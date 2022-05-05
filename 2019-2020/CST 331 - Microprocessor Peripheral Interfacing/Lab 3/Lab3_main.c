/*******************************************************************************
* Name: Zak Rowland
* Date: 2/13/2020
* CST 331 Lab: 3
* Description: Introduction to EBI
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
#pragma config FPLLMULT = MUL_64  // System PLL Multiplier (PLL Multiply by 64) FVco = 6MHz * 64 = 384MHz (350 < FVco < 700)
#pragma config FPLLODIV = DIV_4   // System PLL Output Clock Divider (4x Divider) 384MHz / 4 = 96 MHz
//#pragma config FPLLMULT = MUL_112       // System PLL Multiplier (PLL Multiply by 112) 6MHz * 112 = 672MHz
//#pragma config FPLLODIV = DIV_8         // System PLL Output Clock Divider (8x Divider) 672MHz / 8 = 84MHz

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

// Global Defines
#define SRAM_ADDR_CS0 0xE0000000
#define RAM_SIZE 2*1024*1024
#include <xc.h>
#include <stdint.h>

/* Pinout:
 * /EBICS0 = P131 = RJ4 = 2-12
 * EBIA1 = P51 = RK1 = 2-36
 * EBIA0 = P30 = RJ15 = 2-32
 * /EBIBS1 = P10 = RJ10 = 2-22
 * /EBIBS0 = P9 = RJ12 = 2-26
 * /EBIOE = P13 = RC4 = 1-11
 * /EBIWE = P12 = RC3 = 1-13
 */

int main(void){
    int loop_count = 0;
    uint32_t * addr = NULL;
    uint32_t value = 0;
    
    // Enable address lines [0:19]
    CFGEBIA = 0x800FFFFF;
    
    CFGEBIC = _CFGEBIC_EBIWEEN_MASK |
              _CFGEBIC_EBIOEEN_MASK |
              //_CFGEBIC_EBIBSEN1_MASK | //to disable 16bit mode
              //_CFGEBIC_EBIBSEN0_MASK | //to disable 16bit mode
              _CFGEBIC_EBICSEN0_MASK |
              //_CFGEBIC_EBIDEN1_MASK | //to disable 16bit mode
              _CFGEBIC_EBIDEN0_MASK;

    //Set CS0 to base physical address 0z20000000
    EBICS0 = 0x20000000;     
    
    EBIMSK0 = ((6 << _EBIMSK0_MEMSIZE_POSITION) &
                     _EBIMSK0_MEMSIZE_MASK) |
              // 2^(6+15) = 2^21 = 2MB
              ((1 << _EBIMSK0_MEMTYPE_POSITION) &
                     _EBIMSK0_MEMTYPE_MASK) |
              // 1 = SRAM
              ((0 << _EBIMSK0_REGSEL_POSITION) &
                     _EBIMSK0_REGSEL_MASK);
              // Use Timing Reg set 0    

    EBISMT0 = //((7 << _EBISMT0_TBTA_POSITION) &
              //        _EBISMT0_TBTA_MASK) | 
              ((0 << _EBISMT0_PAGESIZE_POSITION) &
                      _EBISMT0_PAGESIZE_MASK) |
              ((1 << _EBISMT0_PAGEMODE_POSITION) &
                      _EBISMT0_PAGEMODE_MASK) |
              ((1 << _EBISMT0_TPRC_POSITION) &
                      _EBISMT0_TPRC_MASK) |
              ((10 << _EBISMT0_TRC_POSITION) &
                      _EBISMT0_TRC_MASK) |
              (( 3 << _EBISMT0_TAS_POSITION) &
                      _EBISMT0_TAS_MASK) |
              (( 1 << _EBISMT0_TWR_POSITION) &
                      _EBISMT0_TWR_MASK) |
              ((10 << _EBISMT0_TWP_POSITION) &
                      _EBISMT0_TWP_MASK);
    // TBTA, TPRC, PAGEMODE, PAGESIZE and
    // RDYMODE bits all 0

    //EBISMCON = 0x00000000; //Keep default data width to 16-bits
    EBISMCON = ((4 << _EBISMCON_SMDWIDTH0_POSITION) &
                     _EBISMCON_SMDWIDTH0_MASK); //Set mode to 8 bits
    addr = (uint32_t *)SRAM_ADDR_CS0;
    while(1) {
        // Your code added here
        //*addr = 0xAA55AA55;
        //value = *addr;
        //asm("nop"); // for a breakpoint
        
        //asm("lui $at, 0xE000; sw $at, 4($at); lw $0, 0($at)");
        
        //asm("lwr %0, 0xE0000001":"=r"(value));
        //asm("swr %0, 0xE0000001"::"r"(0xAA55AA55));
        //asm("nop"); // for a breakpoint
        
        //value = *addr;
        //asm("nop"); // for a breakpoint
        
        asm("lwr %0, 0xE0000002":"=r"(value));
        asm("nop"); // for a breakpoint
    }
    return (1);
}