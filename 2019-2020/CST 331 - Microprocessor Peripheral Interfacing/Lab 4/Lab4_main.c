/*******************************************************************************
* Name: Zak Rowland
* Date: 2/27/2020
* CST 331 Lab: 4
* Description: EBI and External Memory
*******************************************************************************/
//Begin hardware configuration
#if defined(__32MZ2048EFG144__)
#pragma config FPLLIDIV = DIV_4
// System PLL Input Divider (4x Divider) for 24MHz clock (Rev D (C1) board) 24MHz/2 = 6MHz
#pragma config UPLLFSEL = FREQ_24MHZ 
// USB PLL Input Frequency Selection (USB PLL input is 24 MHz)
#else
#pragma config FPLLIDIV = DIV_2
// System PLL Input Divider (2x Divider) for 12 MHz crystal (Rev B and C boards) 12MHz/2 = 6MHz
#pragma config UPLLEN = OFF
// USB PLL Enable (USB PLL is disabled)
#endif
#pragma config FPLLRNG = RANGE_5_10_MHZ
// System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_POSC
// System PLL Input Clock Selection (POSC is input to the System PLL)
#pragma config FPLLMULT = MUL_64
// System PLL Multiplier (PLL Multiply by 64) FVco = 6MHz * 64 = 384MHz (350 < FVco < 700)
#pragma config FPLLODIV = DIV_4
// System PLL Output Clock Divider (4x Divider) 384MHz / 4 = 96 MHz
//#pragma config FPLLMULT = MUL_112
// System PLL Multiplier (PLL Multiply by 112) 6MHz * 112 = 672MHz
//#pragma config FPLLODIV = DIV_8
// System PLL Output Clock Divider (8x Divider) 672MHz / 8 = 84MHz

// DEVCFG1
#pragma config FNOSC = SPLL
// Oscillator Selection Bits (Primary Osc (HS,EC))
#pragma config FSOSCEN = OFF
// Secondary Oscillator Enable (Disable SOSC)
#if defined(__32MZ2048EFG144__)
#pragma config POSCMOD = EC
// Primary Oscillator Configuration EC - External clock osc
#else
#pragma config POSCMOD = HS
// Primary Oscillator Configuration HS - Crystal osc
#endif
#pragma config FCKSM = CSDCMD
// Clock Switching and Monitor Selection (Clock Switch Disabled, FSCM Disabled)
#pragma config FWDTEN = OFF
// Watchdog Timer Enable (WDT Disabled)
#pragma config FDMTEN = OFF
// Deadman Timer Enable (Deadman Timer is disabled)
#pragma config DMTINTV = WIN_127_128
// Default DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config DMTCNT = DMT31
// Max Deadman Timer count = 2^31

// DEVCFG0
#pragma config JTAGEN = OFF
// JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx2
// ICE/ICD Comm Channel Select (Communicate on PGEC2/PGED2)
//End hardware configuration

// Global Defines
#define SRAM_ADDR_CS0 0xE0000000
#define RAM_SIZE 8*1024*2
#include <xc.h>
#include <stdint.h>

#define WARNING_LED _LATH_LATH2_MASK

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
    uint16_t loop_count_16bit = 0;
    uint32_t * addr_32bit = NULL;
    uint16_t * addr_16bit = NULL;
    uint8_t * addr_8bit = NULL;
    uint32_t value_32bit = 0;
    uint16_t value_16bit = 0;
    uint8_t value_8bit = 0;
    
    uint8_t * addr_next_odd = NULL;
    
    ANSELH = 0;
    TRISHCLR = _TRISH_TRISH2_MASK;
    LATHCLR = WARNING_LED;
    
    // Enable address lines [12:0]
    CFGEBIA = 0x80001FFF;
    
    CFGEBIC = _CFGEBIC_EBIWEEN_MASK |
              _CFGEBIC_EBIOEEN_MASK |
              _CFGEBIC_EBIBSEN1_MASK | //comment to disable 16bit mode
              _CFGEBIC_EBIBSEN0_MASK | //comment to disable 16bit mode
              _CFGEBIC_EBICSEN0_MASK |
              _CFGEBIC_EBIDEN1_MASK | //comment to disable 16bit mode
              _CFGEBIC_EBIDEN0_MASK;

    //Set CS0 to base physical address 0z20000000
    EBICS0 = 0x20000000;     
    
    EBIMSK0 = ((1 << _EBIMSK0_MEMSIZE_POSITION) &
                     _EBIMSK0_MEMSIZE_MASK) |
              // 64KB min
              ((1 << _EBIMSK0_MEMTYPE_POSITION) &
                     _EBIMSK0_MEMTYPE_MASK) |
              // 1 = SRAM
              ((0 << _EBIMSK0_REGSEL_POSITION) &
                     _EBIMSK0_REGSEL_MASK);
              // Use Timing Reg set 0    

    EBISMT0 = ((3 << _EBISMT0_TRC_POSITION) & //was 63
                      _EBISMT0_TRC_MASK) |
              (( 1 << _EBISMT0_TAS_POSITION) & //was 3
                      _EBISMT0_TAS_MASK) |
              (( 1 << _EBISMT0_TWR_POSITION) & //was 3
                      _EBISMT0_TWR_MASK) |
              ((3 << _EBISMT0_TWP_POSITION) & //was 63
                      _EBISMT0_TWP_MASK);
    // TBTA, TPRC, PAGEMODE, PAGESIZE and RDYMODE bits all 0

    EBISMCON = 0x00000000; //Keep default data width to 16-bits
    
    while(1) {
        // Program 1 Tests *****************************************************
        // Test 1 Write ********************************************************
        addr_8bit = (uint8_t *)SRAM_ADDR_CS0;
        for(loop_count = 0; loop_count < RAM_SIZE/4; loop_count++)
        {
            *addr_8bit++ = 0x00;
            *addr_8bit++ = 0xFF;
            *addr_8bit++ = 0xAA;
            *addr_8bit++ = 0x55;
        }
        // Test 1 Read *********************************************************
        addr_8bit = (uint8_t *)SRAM_ADDR_CS0;
        for(loop_count = 0; loop_count < RAM_SIZE/4; loop_count++)
        {
            value_8bit = *addr_8bit++;
            if(value_8bit != 0x00)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
            value_8bit = *addr_8bit++;
            if(value_8bit != 0xFF)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
            value_8bit = *addr_8bit++;
            if(value_8bit != 0xAA)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
            value_8bit = *addr_8bit++;
            if(value_8bit != 0x55)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
        }
        // Test 2 Write ********************************************************
        addr_8bit = (uint8_t *)SRAM_ADDR_CS0;
        addr_8bit += 1000;
        
        for(loop_count = 0; loop_count < RAM_SIZE/4; loop_count++)
        {
            *addr_8bit++ = 0xFF;
            *addr_8bit++ = 0xAA;
            *addr_8bit++ = 0x55;
            *addr_8bit++ = 0x00;
        }
        // Test 2 Read *********************************************************
        addr_8bit = (uint8_t *)SRAM_ADDR_CS0;
        addr_8bit += 1000;
        
        for(loop_count = 0; loop_count < RAM_SIZE/4; loop_count++)
        {
            value_8bit = *addr_8bit++;
            if(value_8bit != 0xFF)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
            value_8bit = *addr_8bit++;
            if(value_8bit != 0xAA)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
            value_8bit = *addr_8bit++;
            if(value_8bit != 0x55)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
            value_8bit = *addr_8bit++;
            if(value_8bit != 0x00)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
        }
        // Test 3 Write ********************************************************
        addr_8bit = (uint8_t *)SRAM_ADDR_CS0;
        addr_8bit += 2000;
        
        for(loop_count = 0; loop_count < RAM_SIZE/4; loop_count++)
        {
            *addr_8bit++ = 0xAA;
            *addr_8bit++ = 0x55;
            *addr_8bit++ = 0x00;
            *addr_8bit++ = 0xFF;
        }
        // Test 3 Read *********************************************************
        addr_8bit = (uint8_t *)SRAM_ADDR_CS0;
        addr_8bit += 2000;
        
        for(loop_count = 0; loop_count < RAM_SIZE/4; loop_count++)
        {
            value_8bit = *addr_8bit++;
            if(value_8bit != 0xAA)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
            value_8bit = *addr_8bit++;
            if(value_8bit != 0x55)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
            value_8bit = *addr_8bit++;
            if(value_8bit != 0x00)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
            value_8bit = *addr_8bit++;
            if(value_8bit != 0xFF)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
        }
        // Test 4 Write ********************************************************
        addr_8bit = (uint8_t *)SRAM_ADDR_CS0;
        addr_8bit += 3000;
        
        for(loop_count = 0; loop_count < RAM_SIZE/4; loop_count++)
        {
            *addr_8bit++ = 0x55;
            *addr_8bit++ = 0x00;
            *addr_8bit++ = 0xFF;
            *addr_8bit++ = 0xAA;
        }
        // Test 4 Read *********************************************************
        addr_8bit = (uint8_t *)SRAM_ADDR_CS0;
        addr_8bit += 3000;
        
        for(loop_count = 0; loop_count < RAM_SIZE/4; loop_count++)
        {
            value_8bit = *addr_8bit++;
            if(value_8bit != 0x55)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
            value_8bit = *addr_8bit++;
            if(value_8bit != 0x00)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
            value_8bit = *addr_8bit++;
            if(value_8bit != 0xFF)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
            value_8bit = *addr_8bit++;
            if(value_8bit != 0xAA)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
        }
        // End Program 1 Tests *************************************************
        // *********************************************************************
        // Program 2 Tests *****************************************************
        addr_16bit = (uint16_t *)SRAM_ADDR_CS0;
        for(loop_count_16bit = 0x0000; loop_count_16bit < (RAM_SIZE / 2); loop_count_16bit++)
        {
            *addr_16bit++ = loop_count_16bit;
        }
        
        addr_32bit = (uint32_t *)SRAM_ADDR_CS0;
        //addr_32bit += 4; //This will cause failure
        for(loop_count = 0; loop_count < (RAM_SIZE / 4); loop_count+=2)
        {
            value_32bit = *addr_32bit++;
            if((value_32bit & 0x0000FFFF) != loop_count)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
            else if(((value_32bit & 0xFFFF0000) >> 16) != loop_count + 1)
            {
                while(1)
                {
                    LATHINV = _LATH_LATH2_MASK;
                    for(loop_count = 0; loop_count < 500000; loop_count++){}
                }
            }
        }
        // End Program 2 Tests *************************************************
        // *********************************************************************
        // Tests for measuring timing ******************************************
        // Test write cycle ****************************************************
        addr_8bit = (uint8_t *)SRAM_ADDR_CS0;
        addr_32bit = (uint32_t *)SRAM_ADDR_CS0;
        
        *addr_8bit++ = 0x55;
        *addr_8bit++ = 0xFF;
        *addr_8bit++ = 0xAA;
        *addr_8bit++ = 0x55;
        
        value_32bit = *addr_32bit;
        // Test read cycle ***************************************************** 
        addr_8bit = (uint8_t *)SRAM_ADDR_CS0;
        addr_8bit += 1;
        addr_next_odd = addr_8bit + 2;
        
        *addr_8bit = 0x01;
        *addr_next_odd = 0x00;
        value_8bit = *addr_8bit;
        value_8bit = *addr_next_odd;
        // End Tests for measuring timing **************************************
        // *********************************************************************
        loop_count = 0;
    }
    return (1);
}