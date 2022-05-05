/*******************************************************************************
* Name: Zak Rowland
* Date: 1/21/2020
* CST 331 Lab: 2
* Description: DMA
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

#define VirtToPhys(p) (int)p<0?((int)p&0x1fffffffL):(unsigned int)((unsigned char*)p+0x40000000L)

#define BUFFER_SIZE 8192
#define BLOCK_SIZE 1024
#define RECEIVE_LED _LATH_LATH8_MASK
#define TRANSMIT_LED _LATH_LATH9_MASK
#define BUFFER_OVERFLOW_LED _LATH_LATH15_MASK
#define BUTTON_MASK PORTHbits.RH6

char __attribute__((coherent)) transfer_buffer[BUFFER_SIZE] = {0};
int __attribute__((coherent)) led_mask = _LATH_LATH8_MASK;
int __attribute__((coherent)) timer_mask = 0x8000;

int original_buffer_ptr = 0;

static volatile uint8_t button_pressed = 0;
static volatile uint8_t transmit_start = 0;
static volatile uint8_t transmit_busy = 0;
static volatile uint8_t receive_busy = 0;

uint16_t dma_bytes_received = 0;
uint8_t dma_blocks_received = 0;

void __ISR_AT_VECTOR(_DMA0_VECTOR, IPL7SRS) DMAReceive(void)
{
    int dma_flags = DCH0INT & 0xFF; //read the interrupt flags
    
    if(dma_flags & 0x8) //if channel block transfer complete
    {
        DCH0CONCLR = _DCH0CON_CHEN_MASK; //disable DMA channel 0
        dma_blocks_received++; //received another block, increment counter
        if(dma_blocks_received > 7) //if max blocks received
        {
            DCH0DSA = original_buffer_ptr; //reset destination pointer and leave channel off
        }
        else 
        {
            DCH0DSA = DCH0DSA + BLOCK_SIZE; //move DMA0 destination address ahead by 1024 bytes
            DCH0CONSET = _DCH0CON_CHEN_MASK; //enable DMA channel 0
            //the ending breakpoint for step 8 (block complete interrupt latency) 
        }
        IFS3CLR = _IFS3_U1RXIF_MASK; //clear rx interrupt flag
    }    
    DCH0INTCLR = 0x000000FF; //clear the dma 0 channel interrupt flags
    IFS4CLR = _IFS4_DMA0IF_MASK; //clear the dma 0 interrupt flag
}

void __ISR_AT_VECTOR(_DMA1_VECTOR, IPL6SRS) DMATransfer(void)
{
    int dma_flags = DCH1INT & 0xFF; //read the interrupt flags
    
    if(dma_flags & 0x8) //if channel block transfer complete
    {
        DCH1CONCLR = _DCH1CON_CHEN_MASK; //disable DMA channel 1
        if(dma_blocks_received == 0 || (dma_blocks_received == 1 && dma_bytes_received == 0))
        { //if there are 0 blocks left or 1 full block and 0 additional bytes
            dma_blocks_received = 0; //reset byte count
            dma_bytes_received = 0; //reset block count
            DCH1SSA = original_buffer_ptr; //reset DMA1 source address
            IFS3CLR = _IFS3_U1RXIF_MASK; //clear rx interrupt flag
            DCH0DSA = original_buffer_ptr; //reset DMA0 destination address
            LATHCLR = TRANSMIT_LED; //turn off status LED
            transmit_busy = 0; //no longer busy
            DCH0CONSET = _DCH0CON_CHEN_MASK; //enable DMA channel 0
        }
        else
        {
            dma_blocks_received--; //sent a block, decrement block count
            DCH1SSA = DCH1SSA + BLOCK_SIZE; //move DMA1 source address ahead by 1024 bytes
            DCH1CONSET = _DCH1CON_CHEN_MASK; //enable DMA channel 1
            DCH0CONCLR = _DCH0CON_CHEN_MASK; //disable DMA channel 0
        }
        
        if(dma_blocks_received == 0 && dma_bytes_received != 0) //if a partial block remains
        {
            DCH1SSIZ = dma_bytes_received; //update DMA1 source size to size of partial block
            dma_bytes_received = 0; //reset byte count
            DCH1CONSET = _DCH1CON_CHEN_MASK; //enable DMA channel 1
        }
    }
    DCH1INTCLR = 0x000000FF; //clear the dma 1 channel interrupt flags
    IFS4CLR = _IFS4_DMA1IF_MASK; //clear the dma 1 interrupt flag
}

void __ISR_AT_VECTOR(_TIMER_5_VECTOR, IPL4SRS) TIMERon(void)
{

        LATHCLR = RECEIVE_LED; //turn off status LED
        T4CONCLR = timer_mask; //turn off Timer5
        IFS0CLR = _IFS0_T5IF_MASK; //clear the Timer5 interrupt flag
}


void InitializeUART(void);
void InitializeDebounceTimer(void);
void InitializeLEDTimer(void);
void InitializeForDMA(void);

int main()
{
    original_buffer_ptr = VirtToPhys((void*)&transfer_buffer);
            
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
   
    INTCONSET = _INTCON_MVEC_MASK; //Set the MVEC bit for multi-vector mode
	
    InitializeLEDTimer(); //Setup LED timer
    InitializeUART(); //Setup UART
    InitializeDebounceTimer(); //Setup debouncing timer
    InitializeForDMA(); //Setup DMA channels
	//Set priority 7 to use shadow set 7, priority 6 to use shadow set 6, 
    //  priority 5 to use shadow set 5, and priority 4 to use shadow set 4
    PRISS = ((7 << _PRISS_PRI7SS_POSITION) & _PRISS_PRI7SS_MASK) 
            | ((6 << _PRISS_PRI6SS_POSITION) & _PRISS_PRI6SS_MASK) 
            | ((5 << _PRISS_PRI5SS_POSITION) & _PRISS_PRI5SS_MASK) 
            | ((4 << _PRISS_PRI4SS_POSITION) & _PRISS_PRI4SS_MASK);
    asm volatile("ei"); //Enable all interrupts
   
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
            transmit_busy = 1; //set busy transmission flag
            dma_bytes_received = DCH0DPTR;
            if(dma_bytes_received == 0 && dma_blocks_received == 0)
            {
                transmit_busy = 0;
                DCH1CONCLR = _DCH1CON_CHEN_MASK; //disable DMA channel 1
            }
            else
            {
                LATHSET = TRANSMIT_LED; //turn on status LED
                if(dma_blocks_received == 0) DCH1SSIZ = dma_bytes_received;
                else DCH1SSIZ = BLOCK_SIZE;
                DCH0CONCLR = _DCH0CON_CHEN_MASK; //disable DMA channel 0
                DCH1CONSET = _DCH1CON_CHEN_MASK; //enable DMA channel 1
            }
        }
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
    //Sets the TX interrupt mode to 0, interrupt flag is asserted while transmit buffer contains at least one empty space
    U1RXREG = 0x0; //Reset U1RX FIFO
    //U1TXREG = 0x0; //Reset U1TX FIFO
    
    U1BRG = 45; //Baud rate = 114,130.43478
    
    U1STASET = _U1STA_UTXEN_MASK | _U1STA_URXEN_MASK; //Set the UTXEN and URXEN bits to enable UART transmitter and receiver
    //U1STASET = (1 << _U1STA_UTXISEL_POSITION) & _U1STA_UTXISEL_MASK; //Set TX interrupt mode to 1, interrupt is generated and asserted when all characters have been transmitted
    U1MODESET = (2 << _U1MODE_UEN_POSITION) & _U1MODE_UEN_MASK; //U1TX, U1RX, /U1CTS, /U1RTS are enabled and used
    U1MODECLR = _U1MODE_RTSMD_MASK; //Enable flow control mode
    U1MODESET = _U1MODE_ON_MASK; //Set the ON bit to enable the UART
	
	//configure UART1 RX/TX interrupts
    IPC28CLR = (_IPC28_U1TXIP_MASK | _IPC28_U1TXIS_MASK | _IPC28_U1RXIP_MASK | _IPC28_U1RXIS_MASK); //Clear the U1RX and U1TX priority and subpriority bits
	IPC28SET = (5 << _IPC28_U1RXIP_POSITION) & _IPC28_U1RXIP_MASK; //Set U1RX priority to 5 and subpriority to 0
    IPC28SET = (4 << _IPC28_U1TXIP_POSITION) & _IPC28_U1TXIP_MASK; //Set U1TX priority to 4 and subpriority to 0
    IFS3CLR = _IFS3_U1RXIF_MASK | _IFS3_U1TXIF_MASK; //Clear the U1RX and U1TX interrupt flags
    //IEC3SET = _IEC3_U1RXIE_MASK; //Set the U1RX interrupt enable bits
    //IEC3CLR = _IEC3_U1TXIE_MASK; //Clear the U1TX interrupt enable bits
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
    T4CON = 0x0; //stop any Timer4 operation
    T4CON = ((5 << _T4CON_TCKPS_POSITION) & _T4CON_TCKPS_MASK) | _T4CON_T32_MASK; //Set T4CON for a prescale value of 5 (1:32), all other bits are 0
    TMR4 = 0x0; //initialize Timer4 to 0
    PR4 = 1312500; //count to 1,312,500 for 0.5s at 84MHz prescaled by 1:32
	
 

    IPC6CLR = (_IPC6_T5IP_MASK | _IPC6_T5IS_MASK); //Clear the Timer5 priority and subpriority bits
    IPC6SET = (3 << _IPC6_T5IP_POSITION) & _IPC6_T5IP_MASK; //Set Timer5 priority to 3 and subpriority to 0
    IFS0CLR = _IFS0_T5IF_MASK; //clear the Timer5 interrupt flag
    IEC0SET = _IEC0_T5IE_MASK; //enable Timer5 interrupts*/
}

void InitializeForDMA(void)
{
    DMACONSET = _DMACON_ON_MASK; //enable the DMA controller
    //configure DMA channel 0 - receive
    DCH0CON = 0x0; //turn channel 0 off and clear config
    DCH0ECON = ((113 << _DCH0ECON_CHSIRQ_POSITION) & _DCH0ECON_CHSIRQ_MASK) | _DCH0ECON_SIRQEN_MASK; //set channel 0 transfer start IRQ to U1RX
    DCH0CONSET = _DCH0CON_CHAED_MASK; //allow events if disabled
    DCH0CONSET = ((3 << _DCH0CON_CHPRI_POSITION) & _DCH0CON_CHPRI_MASK); //set priority to 3, no chaining
    DCH0SSA = VirtToPhys((void*)&U1RXREG); //convert U1RXREG address to physical and set as DMA0 source
    DCH0DSA = VirtToPhys((void*)&transfer_buffer); //convert buffer address to physical and set as DMA0 destination
    DCH0SSIZ = 1; //source size of 1 byte
    DCH0DSIZ = BLOCK_SIZE; //destination size of 1024 bytes
    DCH0CSIZ = 1; //1 byte transferred per event
    DCH0INTCLR = 0x00FF00FF; //clear existing DMA0 events, disable all interrupts
    DCH0INTSET = _DCH0INT_CHBCIE_MASK; //enable block transfer complete interrupt
    DCH0CONSET = _DCH0CON_CHEN_MASK; //enable DMA channel 0
    //DCH0DPTR
    
    //configure DMA channel 1 - transfer
    DCH1CON = 0x0; //turn channel 1 off and clear config
    DCH1ECON = ((114 << _DCH1ECON_CHSIRQ_POSITION) & _DCH1ECON_CHSIRQ_MASK) | _DCH1ECON_SIRQEN_MASK; //set channel 1 transfer start IRQ to U1TX
    DCH1CONSET = _DCH1CON_CHAED_MASK; //allow events if disabled
    DCH1CONSET = ((2 << _DCH1CON_CHPRI_POSITION) & _DCH1CON_CHPRI_MASK); //set priority to 2, no chaining
    DCH1SSA = VirtToPhys((void*)&transfer_buffer); //convert buffer address to physical and set as DMA1 source
    DCH1DSA = VirtToPhys((void*)&U1TXREG); //convert U1TXREG address to physical and set as DMA1 destination
    DCH1SSIZ = BLOCK_SIZE; //source size of 1024 bytes
    DCH1DSIZ = 1; //destination size of 1 byte
    DCH1CSIZ = 1; //1 byte transferred per event
    DCH1INTCLR = 0x00FF00FF; //clear existing DMA1 events, disable all interrupts
    DCH1INTSET = _DCH1INT_CHBCIE_MASK; //enable block transfer complete interrupt
    //DCH1CONSET = _DCH1CON_CHEN_MASK; //enable DMA channel 1
	
    //configure DMA channel 2 - turn on LED
    DCH2CON = 0x0; //turn channel 2 off and clear config
    DCH2ECON = ((113 << _DCH2ECON_CHSIRQ_POSITION) & _DCH2ECON_CHSIRQ_MASK) | _DCH2ECON_SIRQEN_MASK; //set channel 2 transfer start IRQ to U1RX
    DCH2CONSET = ((1 << _DCH2CON_CHPRI_POSITION) & _DCH2CON_CHPRI_MASK); //set priority to 1, no chaining
    DCH2CONSET = _DCH2CON_CHAEN_MASK; //enable automatic enable
    DCH2SSA = VirtToPhys((void*)&led_mask); //convert LED mask to physical and set as DMA2 source
    DCH2DSA = VirtToPhys((void*)&LATHSET); //convert LATH address to physical and set as DMA2 destination
    DCH2SSIZ = 2; //source size of 2 bytes
    DCH2DSIZ = 2; //destination size of 2 bytes
    DCH2CSIZ = 2; //2 bytes transferred per event
    DCH2INTCLR = 0x00FF00FF; //clear existing DMA2 events, disable all interrupts
    DCH2INTSET = _DCH2INT_CHBCIE_MASK; //enable block transfer complete interrupt
    DCH2CONSET = _DCH2CON_CHEN_MASK; //enable DMA channel 2
    
    //configure DMA channel 3 - turn on Timer4/5
    DCH3CON = 0x0; //turn channel 2 off and clear config
    DCH3ECON = ((113 << _DCH3ECON_CHSIRQ_POSITION) & _DCH3ECON_CHSIRQ_MASK) | _DCH3ECON_SIRQEN_MASK; //set channel 3 transfer start IRQ to U1RX
    DCH3CONSET = ((0 << _DCH3CON_CHPRI_POSITION) & _DCH3CON_CHPRI_MASK); //set priority to 0, no chaining
    DCH3CONSET = _DCH3CON_CHAEN_MASK; //enable automatic enable
    DCH3SSA = VirtToPhys((void*)&timer_mask); //convert timer mask to physical and set as DMA3 source
    DCH3DSA = VirtToPhys((void*)&T4CONSET); //convert T4CON address to physical and set as DMA3 destination
    DCH3SSIZ = 2; //source size of 2 bytes
    DCH3DSIZ = 2; //destination size of 2 bytes
    DCH3CSIZ = 2; //2 bytes transferred per event
    DCH3INTCLR = 0x00FF00FF; //clear existing DMA3 events, disable all interrupts
    DCH3INTSET = _DCH3INT_CHBCIE_MASK; //enable block transfer complete interrupt
    DCH3CONSET = _DCH3CON_CHEN_MASK; //enable DMA channel 3
    
	//configure DMA0 and DMA1 interrupts
    IPC33CLR = (_IPC33_DMA0IP_MASK | _IPC33_DMA0IS_MASK | _IPC33_DMA1IP_MASK | _IPC33_DMA1IS_MASK); //clear the DMA0 and DMA1 priority and subpriority bits
    IPC33SET = (7 << _IPC33_DMA0IP_POSITION) & _IPC33_DMA0IP_MASK; //set DMA0 priority to 7 and subpriority to 0
    IPC33SET = (6 << _IPC33_DMA1IP_POSITION) & _IPC33_DMA1IP_MASK; //set DMA1 priority to 6 and subpriority to 0
    IFS4CLR = _IFS4_DMA0IF_MASK | _IFS4_DMA1IF_MASK; //clear the DMA0 and DMA1 interrupt flags
    IEC4SET = _IEC4_DMA0IE_MASK | _IEC4_DMA1IE_MASK; //set the DMA0 and DMA1 interrupt enable bits
    
}