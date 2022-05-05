/*******************************************************************************
* Name: Zak Rowland
* Date: 10/3/2019
* Lab: 1
* Description: Introduction to C on the PIC32MZ
*******************************************************************************/
// PIC32MZ2048ECG144 or EFG144 based HMZ144 board Configuration Bit Settings
// DEVCFG2
int global_var = 0;
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

#include <xc.h>
//LATH address: 0xBF860730
//LED connected to port H bit 2
//PBCLK3 is 21MHz
int main(){
    int local_var = 0;
    TRISHCLR = 0x0004; //Set PORTH bit 2 as an output.
    ANSELHCLR = 0x0004; //Set PORTH bit 2 as digital instead of analog.
    
    SYSKEY = 0; //Ensure lock
    SYSKEY = 0xAA996655; //Write key 1
    SYSKEY = 0x556699AA; //Write key 2
    
    PB3DIV = _PB3DIV_ON_MASK | 3 & _PB3DIV_PBDIV_MASK; 
    //0 = div by 1, 1 = div by 2
    
    //Set T2CON for a prescale value of 7 (1:256), all other bits are 0
    T2CON = ((7 << _T2CON_TCKPS_POSITION) & _T2CON_TCKPS_MASK);
    
    TMR2 = 0; //Initialize Timer2 to 0
    PR2 = 100; //Count to half of 82031 (the frequency after prescaling)
    T2CONSET = _T2CON_TON_MASK; //turn on timer2
    while(1){
        //LATH |= _LATH_LATH2_MASK; //Set bit 2 of LATH
        //LATHbits.LATH2 = 1; //Set bit 2 of LATH
        //LATHSET = _LATH_LATH2_MASK; //Set bit 2 of LATH
        //LATH &= ~_LATH_LATH2_MASK; //Clear bit 2 of LATH
        if((IFS0 & _IFS0_T2IF_MASK)){
            LATHINV = _LATH_LATH2_MASK; //Invert bit 2 of LATH
            IFS0INV = _IFS0_T2IF_MASK; //Reset timer 2 interrupt flag
        }
        global_var = 1;
        local_var = 1;
    }
    return 0;
}