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

#define TRANSMIT_LED _LATH_LATH9_MASK

int __attribute__((coherent)) led_mask = TRANSMIT_LED;

void InitializeForDMA(void);

int main()
{
    unsigned int for_count = 0;
    
    PRECON = (1 & _PRECON_PFMWS_MASK) | ((2 << _PRECON_PREFEN_POSITION) & _PRECON_PREFEN_MASK); //Change wait state value to 1 and enable prefetch
    
    SYSKEY = 0; //Ensure lock
    SYSKEY = 0xAA996655; //Write key 1
    SYSKEY = 0x556699AA; //Write key 2
    PB3DIV = _PB3DIV_ON_MASK | 0 & _PB3DIV_PBDIV_MASK; //0 = div by 1 (PBCLK3 = 84MHz)
    PB2DIV = _PB2DIV_ON_MASK | 0 & _PB2DIV_PBDIV_MASK; //0 = div by 1 (PBCLK2 = 84MHz)
    SYSKEY = 0; //Ensure lock
    
    ANSELH = 0; //Not using any analog functions, set to all digital
    TRISHCLR = _TRISH_TRISH9_MASK; //Set LEDs as output
    LATHCLR = TRANSMIT_LED; //Turn off LEDs
    
    ANSELD = 0; //Not using any analog functions, set to all digital
    TRISDCLR = _TRISD_TRISD0_MASK; //Set RD0 as output
    PORTDSET = _PORTD_RD0_MASK; //Turn on RD0
   
    INTCONSET = _INTCON_MVEC_MASK; //Set the MVEC bit for multi-vector mode
	
    InitializeForDMA(); //Setup DMA channels
   
    while(1)
    {
        PORTDINV = _PORTD_RD0_MASK; //toggle RD0
        for_count = 0;
        while(for_count < 100)
        {
            for_count++;
        }
    }
    return 0;
}

void InitializeForDMA(void)
{
    DMACONSET = _DMACON_ON_MASK; //enable the DMA controller
    //configure DMA channel 2 - turn toggle LED
    DCH2CON = 0x0; //turn channel 2 off and clear config
    DCH2ECON = ((3 << _DCH2ECON_CHSIRQ_POSITION) & _DCH2ECON_CHSIRQ_MASK) | _DCH2ECON_SIRQEN_MASK; //set channel 2 transfer start IRQ to INT0
    DCH2CONSET = ((3 << _DCH2CON_CHPRI_POSITION) & _DCH2CON_CHPRI_MASK); //set priority to 3, no chaining
    DCH2CONSET = _DCH2CON_CHAEN_MASK; //enable automatic enable
    DCH2SSA = VirtToPhys((void*)&led_mask); //convert LED mask to physical and set as DMA2 source
    DCH2DSA = VirtToPhys((void*)&LATHINV); //convert LATHINV address to physical and set as DMA2 destination
    DCH2SSIZ = 2; //source size of 2 bytes
    DCH2DSIZ = 2; //destination size of 2 bytes
    DCH2CSIZ = 2; //2 bytes transferred per event
    DCH2INTCLR = 0x00FF00FF; //clear existing DMA2 events, disable all interrupts
    DCH2CONSET = _DCH2CON_CHEN_MASK; //enable DMA channel 2
}