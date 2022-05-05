/*******************************************************************************
* Name: Zak Rowland
* Date: 10/17/2019
* Lab: 3
* Description: Interrupts in C
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

unsigned int tmr2_count;
unsigned int tmr3_count;

void __ISR_AT_VECTOR(_TIMER_2_VECTOR, IPL4SOFT) MyTimer2Handler(void)
{
    tmr2_count++;
    IFS0CLR = _IFS0_T2IF_MASK; //clear the interrupt flag
}

void __ISR_AT_VECTOR(_TIMER_3_VECTOR, IPL3SOFT) MyTimer3Handler(void)
{
    tmr3_count++;
    while(TMR3<40){}
    IFS0CLR = _IFS0_T3IF_MASK; //clear the interrupt flag
}

int main(){
   tmr2_count = 0;
   tmr3_count = 0;
   int n = 0;
    
    PRECON = (1 & _PRECON_PFMWS_MASK) | ((2 << _PRECON_PREFEN_POSITION) & _PRECON_PREFEN_MASK); //Change wait state value to 1 and enable prefetch
    
    SYSKEY = 0; //Ensure lock
    SYSKEY = 0xAA996655; //Write key 1
    SYSKEY = 0x556699AA; //Write key 2
    PB3DIV = _PB3DIV_ON_MASK | 0 & _PB3DIV_PBDIV_MASK; //0 = div by 1 (PBCLK3 = 84MHz)
    SYSKEY = 0; //Ensure lock
    
    T2CON = 0x0; //stop any Timer2 operation
    T2CON = ((0 << _T2CON_TCKPS_POSITION) & _T2CON_TCKPS_MASK); //Set T2CON for a prescale value of 0 (1:1), all other bits are 0
    IFS0CLR = _IFS0_T2IF_MASK; //clear Timer2 interrupt flag IFS0<9>
    TMR2 = 0; //initialize Timer2 to 0
    PR2 = 511; //512 counts for Timer2
    
    T3CON = 0x0; //stop any Timer3 operation
    T3CON = ((0 << _T3CON_TCKPS_POSITION) & _T3CON_TCKPS_MASK); //Set T3CON for a prescale value of 0 (1:1), all other bits are 0
    IFS0CLR = _IFS0_T3IF_MASK; //clear Timer3 interrupt flag
    TMR3 = 0; //initialize Timer3 to 0
    PR3 = 999; //1000 counts for Timer3
    
    INTCONSET = _INTCON_MVEC_MASK; //set the MVEC bit for multi-vector mode
    
    IPC2CLR = _IPC2_T2IP_MASK | _IPC2_T2IS_MASK; //clear Timer2 priority and subpriority bits
    IPC2SET = (4 << _IPC2_T2IP_POSITION) & _IPC2_T2IP_MASK; //set priority to 4 and subpriority to 0
    
    IPC3CLR = _IPC3_T3IP_MASK | _IPC3_T3IS_MASK; //clear Timer3 priority and subpriority bits
    IPC3SET = (3 << _IPC3_T3IP_POSITION) & _IPC3_T3IP_MASK; //set priority to 3 and subpriority to 0
    
    IEC0SET = _IEC0_T2IE_MASK; //enable Timer2 interrupts
    IEC0SET = _IEC0_T3IE_MASK; //enable Timer3 interrupts
    
    //PRISS = (7 << _PRISS_PRI7SS_POSITION) & _PRISS_PRI7SS_MASK; //set priority 7 to use shadow set 7
    
    T2CONSET = _T2CON_TON_MASK; //turn on Timer2
    T3CONSET = _T3CON_TON_MASK; //turn on Timer3
    IFS0 = _IFS0_T3IF_MASK; //artificially trigger a Timer3 interrupt
    for(n = 0; n < 2; n++){ //run the following twice so it runs from cache
        TMR2 = 0;
        TMR3 = 5; //needed to get TMR2 and TMR3 in sync
    }
    
    
    asm volatile("ei"); //enable all interrupts
    
    while(1){}
    
    return 0;
}