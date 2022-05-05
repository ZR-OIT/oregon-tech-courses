/*******************************************************************************
* Name: Zak Rowland
* Date: 1/7/2020
* CST 331 Lab: 1
* Description: Asynchronous Serial I/O -- The PIC32MZ UART
*******************************************************************************/
//Begin hardware configuration
#if defined(__32MZ2048EFG144__)
#pragma config FPLLIDIV = DIV_4         // System PLL Input Divider (4x Divider) for 24MHz clock (Rev D (C1) board) 24MHz/2 = 6MHz
#pragma config UPLLFSEL = FREQ_24MHZ    // USB PLL Input Frequency Selection (USB PLL input is 24 MHz)
#else
#pragma config FPLLIDIV = DIV_2         // System PLL Input Divider (2x Divider) for 12 MHz crystal (Rev B and C boards) 12MHz/2 = 6MHz
#pragma config UPLLEN = OFF             // USB PLL Enable (USB PLL is disabled)
#endif
#pragma config FPLLRNG = RANGE_5_10_MHZ // System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_POSC      // System PLL Input Clock Selection (POSC is input to the System PLL)
#pragma config FPLLMULT = MUL_112       // System PLL Multiplier (PLL Multiply by 112) 6MHz * 112 = 672MHz
#pragma config FPLLODIV = DIV_8         // System PLL Output Clock Divider (8x Divider) 672MHz / 8 = 84MHz

// DEVCFG1
#pragma config FNOSC = SPLL             // Oscillator Selection Bits (Primary Osc (HS,EC))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disable SOSC)
#if defined(__32MZ2048EFG144__)
#pragma config POSCMOD = EC             // Primary Oscillator Configuration EC - External clock osc
#else
#pragma config POSCMOD = HS             // Primary Oscillator Configuration HS - Crystal osc
#endif
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disabled, FSCM Disabled)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled)
#pragma config FDMTEN = OFF             // Deadman Timer Enable (Deadman Timer is disabled)
#pragma config DMTINTV = WIN_127_128    // Default DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config DMTCNT = DMT31           // Max Deadman Timer count = 2^31

// DEVCFG0
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (Communicate on PGEC2/PGED2)
//End hardware configuration

#include <xc.h>
#include <sys/attribs.h>

char char_read = ' ';
uint8_t more_chars_to_send = 0;

void __ISR_AT_VECTOR(_UART1_RX_VECTOR, IPL7SRS) UARTService(void)
{
    do{
        while(U1STAbits.URXDA) //give priority to receive
        {
            //read chars from UART
            char_read = U1RXREG;
            more_chars_to_send = 1;
        }
        IFS3CLR = _IFS3_U1RXIF_MASK; //atomically clear U1RXIF
        while(!U1STAbits.UTXBF && more_chars_to_send)
        {
            //send chars to UART
            U1TXREG = char_read;
            more_chars_to_send = 1;
        }
        IFS3CLR = _IFS3_U1TXIF_MASK; //atomically clear U1TXIF
    }while(IFS3bits.U1RXIF || IFS3bits.U1TXIF); //continue until interrupt flags are both clear
}

void InitializeUART(void);
void InitializeForISR(void);

int main()
{
    PRECON = (1 & _PRECON_PFMWS_MASK) | ((2 << _PRECON_PREFEN_POSITION) & _PRECON_PREFEN_MASK); //Change wait state value to 1 and enable prefetch
    
    SYSKEY = 0; //Ensure lock
    SYSKEY = 0xAA996655; //Write key 1
    SYSKEY = 0x556699AA; //Write key 2
    PB2DIV = _PB2DIV_ON_MASK | 0 & _PB2DIV_PBDIV_MASK; //0 = div by 1 (PBCLK2 = 84MHz)
    SYSKEY = 0; //Ensure lock
    
    InitializeUART(); //Setup UART
    InitializeForISR(); //Setup interrupts
    
    //TRISHCLR = _TRISH_TRISH8_MASK; //Set LED as output
    //LATHCLR = _PORTH_RH8_MASK; //Turn off LED
    
    while(1){}
    
    return 0;
}

void InitializeUART(void)
{
    /* Baud Rate Generation for 115,200 baud when BRGH = 0
     * UxBRG = (84MHz / (16 * 115,200)) - 1
     * UxBRG = (84MHz / 1,843,200) - 1
     * UxBRG = 44.57291667 = 45
     * Calculated baud = (84MHz / 16 * (45 + 1))
     * Calculated baud = (84MHz / 736)
     * Calculated baud = 114,130.43478
     * Percent error = (115,200 - 114,130.43478) / 115,200
     * Percent error = 0.92844% */
    
    //8 data bits, no parity, hardware handshaking
    RPD11R = 0x1; //RPD11 is connected to TX output
    U1RXR = 0xE; //RX input is connected to RPD6
    RPD5R = 0x1; //RPD5 is connected to RTS output
    U1CTSR = 0x4; //CTS input is connected to RPD4
    
    U1MODE = 0x0; //Stop and reset any UART1 operation and settings
    //Sets the PDSEL bits to 00 (8 bit data, no parity)(POR)
    //Sets the STSEL bit to 0 (1 stop bit)(POR)
    U1STA = 0x0; //Reset U1 status and control register
    //Sets the RX interrupt mode to 0, interrupt flag is asserted while receive buffer is not empty
    U1RXREG = 0x0; //Reset U1RX FIFO
    //U1TXREG = 0x0; //Reset U1TX FIFO
    
    U1BRG = 45; //Baud rate = 114,130.43478
    
    U1STASET = _U1STA_UTXEN_MASK | _U1STA_URXEN_MASK; //Set the UTXEN and URXEN bits to enable UART transmitter and receiver
    U1STASET = (1 << _U1STA_UTXISEL_POSITION) & _U1STA_UTXISEL_MASK; //Set TX interrupt mode to 1, interrupt is generated and asserted when all characters have been transmitted
    U1MODESET = (2 << _U1MODE_UEN_POSITION) & _U1MODE_UEN_MASK; //U1TX, U1RX, /U1CTS, /U1RTS are enabled and used
    U1MODECLR = _U1MODE_RTSMD_MASK; //Enable flow control mode
    U1MODESET = _U1MODE_ON_MASK; //Set the ON bit to enable the UART
}

void InitializeForISR(void)
{
    INTCONSET = _INTCON_MVEC_MASK; //Set the MVEC bit for multi-vector mode
    IPC28CLR = (_IPC28_U1TXIP_MASK | _IPC28_U1TXIS_MASK | _IPC28_U1RXIP_MASK | _IPC28_U1RXIS_MASK); //Clear the U1RX and U1TX priority and subpriority bits
	IPC28SET = (7 << _IPC28_U1RXIP_POSITION) & _IPC28_U1RXIP_MASK; //Set U1RX priority to 7 and subpriority to 0
    IPC28SET = (7 << _IPC28_U1TXIP_POSITION) & _IPC28_U1TXIP_MASK; //Set U1TX priority to 7 and subpriority to 0
    PRISS = (7 << _PRISS_PRI7SS_POSITION) & _PRISS_PRI7SS_MASK; //Set priority 7 to use shadow set 7
    OFF114 = OFF113; //Point the U1TX vector offset to the same address as the U1RX vector offset
    IFS3CLR = _IFS3_U1RXIF_MASK | _IFS3_U1TXIF_MASK; //Clear the U1RX and U1TX interrupt flags
    IEC3SET = _IEC3_U1RXIE_MASK | _IEC3_U1TXIE_MASK; //Set the U1RX and U1TX interrupt enable bits
    asm volatile("ei"); //Enable all interrupts
}