/*******************************************************************************
* Name: Zak Rowland
* Date: 10/10/2019
* Lab: 2
* Description: Performance Issues
*******************************************************************************/
#define NSAMP 256 //number of samples
#define TPIN (2 * M_PI/NSAMP) //used to generate sinusoidal inputs for the FFT
#define FWD_FFT 0 //0 = forward FFT, 1 = inverse FFT
#define F 8 //cycles of the sine wave in the input array (2-8)

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
#include <math.h>
#include "fourier.h"
#include "ddcmath.h"

float array_in[NSAMP];
float real_array_out[NSAMP];
float imag_array_out[NSAMP];

int main(){
    PRECON = (1 & _PRECON_PFMWS_MASK) | ((2 << _PRECON_PREFEN_POSITION) & _PRECON_PREFEN_MASK); //Change wait state value and enable prefetch
    
    int n = 0; //used for loops
    
    SYSKEY = 0; //Ensure lock
    SYSKEY = 0xAA996655; //Write key 1
    SYSKEY = 0x556699AA; //Write key 2
    PB3DIV = _PB3DIV_ON_MASK | 0 & _PB3DIV_PBDIV_MASK; //0 = div by 1
    SYSKEY = 0; //Ensure lock
    
    T2CON = 0x0; //stop any Timer2 operation
    T3CON = 0x0; //stop any Timer3 operation
    T2CON |= _T2CON_T32_MASK; //enable 32 bit mode, all other bits are 0
    TMR2 = 0; //initialize Timer2 to 0
    PR2 = 0xFFFFFFFF; //count to max 32 bit value 4,294,967,295
    T2CONSET = _T2CON_TON_MASK; //turn on Timer2
    
    for(n; n < NSAMP; n++){ //fill input array with data
        array_in[n] = 200 * sin(F * 2 * DDC_PI / NSAMP * n);
    }
    n = 0;
    
    for(n; n < 2; n++){
        TMR2 = 0;
        fft_float(NSAMP, FWD_FFT, array_in, NULL, real_array_out, imag_array_out);
        TMR2 = 0;
    }
  
    n = 0;
    for(n; n < NSAMP; n++){
        //Overwrite one of the output arrays with magnitude information
        real_array_out[n] = sqrt(pow(real_array_out[n],2) + pow(imag_array_out[n],2));
    }
    
    return 0;
}

