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
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 8192
#define RECEIVE_LED _LATH_LATH8_MASK
#define TRANSMIT_LED _LATH_LATH9_MASK
#define BUFFER_OVERFLOW_LED _LATH_LATH15_MASK
#define BUTTON_MASK PORTHbits.RH6

char char_read = ' ';
char new_item = ' ';
uint8_t more_chars_to_send = 0;
char * head_pointer, * tail_pointer, * beginning_pointer, * end_pointer = NULL;
int num_of_items = 0;
const int max_items = BUFFER_SIZE;
char circular_buffer[BUFFER_SIZE] = {0};

static volatile uint8_t button_pressed = 0;
static volatile uint8_t transmit_start = 0;
static volatile uint8_t transmit_busy = 0;
static volatile uint8_t receive_busy = 0;

void __ISR_AT_VECTOR(_UART1_RX_VECTOR, IPL7SRS) UARTService(void)
{
    do{
        while(U1STAbits.URXDA) //give priority to receive
        {
            //read chars from UART
            //LATHINV = RECEIVE_LED; //toggle status LED for receive
            receive_busy = 1;
            TMR4 = 0x0; //Reset timer
            T4CONSET = _T3CON_TON_MASK; //turn on Timer4
            LATHSET = RECEIVE_LED; //set status LED for receive
            new_item = U1RXREG; //read character
            if(num_of_items < max_items) //buffer isn't full
            {
                *head_pointer = new_item; //store read data
                num_of_items++; //increment item count
                head_pointer++; //increment head pointer
                if(head_pointer > end_pointer) head_pointer = beginning_pointer; //make buffer circular
            }
            else
            {
                LATHSET = BUFFER_OVERFLOW_LED; //illuminate overflow LED
                U1RXREG; //dummy read since buffer is full
            }
        }
        IFS3CLR = _IFS3_U1RXIF_MASK; //atomically clear U1RXIF
        receive_busy = 0; //no longer receiving
        if(num_of_items > 0) more_chars_to_send = 1;
        else 
        {
            IEC3CLR = _IEC3_U1TXIE_MASK; //Clear the U1TX interrupt enable bits
            more_chars_to_send = 0;
        }
        while(!U1STAbits.UTXBF && more_chars_to_send && (transmit_start || transmit_busy))
        {
            //send chars to UART
            transmit_start = 0; //clear start transmission flag
            transmit_busy = 1; //set transmission busy flag
            //LATHINV = TRANSMIT_LED; //toggle status LED for transmit
            TMR4 = 0x0; //Reset timer
            T4CONSET = _T3CON_TON_MASK; //turn on Timer4
            LATHSET = TRANSMIT_LED; //set status LED for transmit
            if(num_of_items > 0) //buffer is not empty
            {
                U1TXREG = *tail_pointer; //transmit a character
                num_of_items--; //decrement item count
                tail_pointer++; //move tail pointer
                if(tail_pointer > end_pointer) tail_pointer = beginning_pointer; //make buffer circular
            }
            else
            {
                IEC3CLR = _IEC3_U1TXIE_MASK; //Clear the U1TX interrupt enable bits
                transmit_busy = 0; //clear transmission busy flag
                more_chars_to_send = 0; //clear chars to send flag
                LATHCLR = BUFFER_OVERFLOW_LED; //clear buffer overflow LED
            }
        }
        IFS3CLR = _IFS3_U1TXIF_MASK; //atomically clear U1TXIF
        //LATHCLR = RECEIVE_LED | TRANSMIT_LED; //Turn off LEDs
    }while(IFS3bits.U1RXIF || (IFS3bits.U1TXIF && IEC3bits.U1TXIE)); //continue until interrupt flags are both clear
}

void __ISR_AT_VECTOR(_TIMER_5_VECTOR, IPL6SRS) LEDService(void)
{
    if(!receive_busy) LATHCLR = RECEIVE_LED; //clear status LED for receive
    if(!transmit_busy) LATHCLR = TRANSMIT_LED; //clear status LED for transmit
    T4CONCLR = _T4CON_TON_MASK; //turn off Timer4
    IFS0CLR = _IFS0_T5IF_MASK; //clear Timer5 interrupt flag
}

void InitializeUART(void);
void InitializeForISR(void);
void InitializeDebounceTimer(void);
void InitializeLEDTimer(void);

int main()
{
    uint8_t previous_button_state = 0;
    uint8_t current_button_state = 0;
    uint8_t debounce_loop_count = 0;
    
    PRECON = (1 & _PRECON_PFMWS_MASK) | ((2 << _PRECON_PREFEN_POSITION) & _PRECON_PREFEN_MASK); //Change wait state value to 1 and enable prefetch
    
    SYSKEY = 0; //Ensure lock
    SYSKEY = 0xAA996655; //Write key 1
    SYSKEY = 0x556699AA; //Write key 2
    PB3DIV = _PB3DIV_ON_MASK | 0 & _PB3DIV_PBDIV_MASK; //0 = div by 1 (PBCLK3 = 84MHz)
    PB2DIV = _PB2DIV_ON_MASK | 0 & _PB2DIV_PBDIV_MASK; //0 = div by 1 (PBCLK2 = 84MHz)
    SYSKEY = 0; //Ensure lock
    
    ANSELH = 0; //Not using any analog functions, set to all digital
    TRISHCLR = _TRISH_TRISH8_MASK | _TRISH_TRISH9_MASK | _TRISH_TRISH15_MASK; //Set LEDs as output
    LATHCLR = RECEIVE_LED | TRANSMIT_LED | BUFFER_OVERFLOW_LED; //Turn off LEDs
    
    TRISHSET = _TRISH_TRISH6_MASK; //set button S4 as input
    CNPUHSET = _CNPUH_CNPUH6_MASK; //enable pullup resistor for button S4
    
    beginning_pointer = circular_buffer; //assign a pointer to beginning of memory space for the buffer
    head_pointer = tail_pointer = beginning_pointer; //point both head and tail to beginning of memory space
    end_pointer = beginning_pointer + max_items - 1; //assign a pointer to end of memory space for the buffer
    
    InitializeLEDTimer(); //Setup LED timer
    InitializeUART(); //Setup UART
    InitializeDebounceTimer(); //Setup debouncing timer
    InitializeForISR(); //Setup interrupts
   
    while(1)
    {
        if(TMR2 == PR2) //if debounce time has passed
        {
            current_button_state = BUTTON_MASK; //1 for unpressed, 0 for pressed
            if(current_button_state != previous_button_state) //if button state has changed
            {
                if(debounce_loop_count == 3) //the state has stayed changed for multiple loops
                {
                    previous_button_state = current_button_state; //update states
                    if(current_button_state != 1) button_pressed = 1; //if pin read low, button is pressed
                    else button_pressed = 0; //else button isn't pressed
                    debounce_loop_count = 0; //reset loop counter
                }
                else debounce_loop_count++; //increment loop counter
            }
            TMR2 = 0; //reset timer count
        }
        
        if(button_pressed == 1 && transmit_busy == 0) //if button is pressed and there isn't a transmission in progress
        {
            IEC3SET = _IEC3_U1TXIE_MASK; //Set the U1TX interrupt enable bits
            transmit_start = 1; //set start transmission flag
        }
        else transmit_start = 0; //clear start transmission flag
    }
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
    
    //8 data bits, no parity, hardware handshaking (CTS/RTS)
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
    PRISS = ((7 << _PRISS_PRI7SS_POSITION) & _PRISS_PRI7SS_MASK) | ((6 << _PRISS_PRI6SS_POSITION) & _PRISS_PRI6SS_MASK); //Set priority 7 to use shadow set 7 and Set priority 6 to use shadow set 6
    OFF114 = OFF113; //Point the U1TX vector offset to the same address as the U1RX vector offset
    IFS3CLR = _IFS3_U1RXIF_MASK | _IFS3_U1TXIF_MASK; //Clear the U1RX and U1TX interrupt flags
    IEC3SET = _IEC3_U1RXIE_MASK; //Set the U1RX interrupt enable bits
    
    IPC6CLR = (_IPC6_T5IP_MASK | _IPC6_T5IS_MASK); //Clear the Timer5 priority and subpriority bits
    IPC6SET = (6 << _IPC6_T5IP_POSITION) & _IPC6_T5IP_MASK; //Set Timer5 priority to 6 and subpriority to 0
    IFS0CLR = _IFS0_T5IF_MASK; //clear the Timer5 interrupt flag
    IEC0SET = _IEC0_T5IE_MASK; //enable Timer5 interrupts*/
    asm volatile("ei"); //Enable all interrupts
}


void InitializeDebounceTimer(void)
{
    T2CON = 0x0; //stop any Timer2 operation
    T2CON = ((5 << _T2CON_TCKPS_POSITION) & _T2CON_TCKPS_MASK); //Set T2CON for a prescale value of 5 (1:32), all other bits are 0
    TMR2 = 0x0; //initialize Timer2 to 0
    PR2 = 13135; //count to 13,135 for 5ms at 84MHz prescaled by 1:32 (39,375 for 15ms)
    T2CONSET = _T2CON_TON_MASK; //turn on Timer2
}

void InitializeLEDTimer(void)
{
    T4CON = 0x0; //stop any Timer3 operation
    T4CON = ((5 << _T3CON_TCKPS_POSITION) & _T3CON_TCKPS_MASK) | _T4CON_T32_MASK; //Set T4CON for a prescale value of 5 (1:32), all other bits are 0
    TMR4 = 0x0; //initialize Timer4 to 0
    PR4 = 1312500; //count to 1,312,500 for 0.5s at 84MHz prescaled by 1:32
    //T4CONSET = _T3CON_TON_MASK; //turn on Timer4
}