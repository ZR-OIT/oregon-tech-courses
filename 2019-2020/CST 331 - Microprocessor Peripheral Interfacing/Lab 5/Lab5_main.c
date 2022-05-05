/*******************************************************************************
* Name: Zak Rowland
* Date: 3/9/2020
* CST 331 Lab: 5
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
#define FPGA_ADDR_CS3 0xE0012000
#define FPGA_INV_ADDR_CS3 0xE0014000
#define RAM_SIZE 8*1024*2
#define SW0_MASK 0x01
#define SW7_MASK 0x80
#define SW1_MASK 0x02
#define COUNTER_DELAY 1000000
#include <xc.h>
#include <stdint.h>

int main(void){
    
    int loop_count = 0;
    uint8_t * ram_addr_8bit = NULL;
    uint8_t ram_value_8bit = 0;
    volatile uint8_t * fpga_addr_8bit = NULL;
    uint8_t fpga_value_8bit = 0;
	uint8_t fpga_led_count = 0;
    
    // Enable address lines [16:0]
    CFGEBIA = 0x8001FFFF;
    
    CFGEBIC = _CFGEBIC_EBIWEEN_MASK |
              _CFGEBIC_EBIOEEN_MASK |
              //_CFGEBIC_EBIBSEN1_MASK | //comment to disable 16bit mode
              //_CFGEBIC_EBIBSEN0_MASK | //comment to disable 16bit mode
              _CFGEBIC_EBICSEN0_MASK | //enable CS0
              _CFGEBIC_EBICSEN3_MASK | //enable CS3
              //_CFGEBIC_EBIDEN1_MASK | //comment to disable 16bit mode
              _CFGEBIC_EBIDEN0_MASK;
    
    EBICS0 = 0x20000000; //Set CS0 to base physical address 0x20000000
    EBICS3 = 0x20012000; //Set CS3 to base physical address 0x20012000
    
    EBIMSK0 = ((1 << _EBIMSK0_MEMSIZE_POSITION) &
                     _EBIMSK0_MEMSIZE_MASK) |
              // 64KB min
              ((1 << _EBIMSK0_MEMTYPE_POSITION) &
                     _EBIMSK0_MEMTYPE_MASK) |
              // 1 = SRAM
              ((0 << _EBIMSK0_REGSEL_POSITION) &
                     _EBIMSK0_REGSEL_MASK);
              // Use Timing Reg set 0    
    
    EBIMSK3 = ((1 << _EBIMSK0_MEMSIZE_POSITION) &
                     _EBIMSK0_MEMSIZE_MASK) |
              // 64KB min
              ((1 << _EBIMSK0_MEMTYPE_POSITION) &
                     _EBIMSK0_MEMTYPE_MASK) |
              // 1 = SRAM
              ((1 << _EBIMSK0_REGSEL_POSITION) &
                     _EBIMSK0_REGSEL_MASK);
              // Use Timing Reg set 1
    
    EBISMT0 = ((3 << _EBISMT0_TRC_POSITION) &
                      _EBISMT0_TRC_MASK) |
              (( 1 << _EBISMT0_TAS_POSITION) & 
                      _EBISMT0_TAS_MASK) |
              (( 1 << _EBISMT0_TWR_POSITION) & 
                      _EBISMT0_TWR_MASK) |
              ((3 << _EBISMT0_TWP_POSITION) & 
                      _EBISMT0_TWP_MASK);
    // TBTA, TPRC, PAGEMODE, PAGESIZE and RDYMODE bits all 0
    
    EBISMT1 = ((2 << _EBISMT1_TRC_POSITION) & 
                      _EBISMT1_TRC_MASK) |
              (( 1 << _EBISMT1_TAS_POSITION) &
                      _EBISMT1_TAS_MASK) |
              (( 1 << _EBISMT1_TWR_POSITION) & 
                      _EBISMT1_TWR_MASK) |
              ((3 << _EBISMT1_TWP_POSITION) &
                      _EBISMT1_TWP_MASK);
    // TBTA, TPRC, PAGEMODE, PAGESIZE and RDYMODE bits all 0
    
    EBISMCON = 0x00000000; //Keep CS0 at default data width of 16 bits
    EBISMCON = ((4 << _EBISMCON_SMDWIDTH1_POSITION) &
                     _EBISMCON_SMDWIDTH1_MASK); //Set CS3 mode to 8 bits
	
    while(1) {   
        // Part 7 - Small tests ----------------------------------------------------------------------
        // Input port test ---------------------------------------------------------------------------
        /*
        fpga_addr_8bit = (uint8_t *) FPGA_ADDR_CS3; // Store KSEG3 address
        fpga_value_8bit = *fpga_addr_8bit; // Read a value from switches
        fpga_value_8bit = 0; // Breakpoint here, check value
       
        //ram_addr_8bit = (uint8_t *) SRAM_ADDR_CS0; // Store KSEG3 address
        //*ram_addr_8bit = 0xFF;
        //ram_value_8bit = *ram_addr_8bit; // Read a value from RAM
        //ram_value_8bit = 0; // Breakpoint here, check value
	   
        // Output port test --------------------------------------------------------------------------
        fpga_addr_8bit = (uint8_t *) FPGA_ADDR_CS3; // Store KSEG3 address
        *fpga_addr_8bit++ = 15;
        for(loop_count = 0; loop_count < COUNTER_DELAY/2; loop_count++){};
        *fpga_addr_8bit++ = 240;
        for(loop_count = 0; loop_count < COUNTER_DELAY/2; loop_count++){};
        *fpga_addr_8bit++ = 255;
        for(loop_count = 0; loop_count < COUNTER_DELAY/2; loop_count++){};
        // End Part 7 --------------------------------------------------------------------------------
	    */
        /*
        // Part 8 - LED Counter ----------------------------------------------------------------------
        fpga_addr_8bit = (uint8_t *) FPGA_ADDR_CS3; // Store KSEG3 address
        fpga_value_8bit = *fpga_addr_8bit; // Read data
        if(fpga_value_8bit & SW0_MASK) // If SW0 is set (reads 1)
        {
            if(fpga_value_8bit & SW7_MASK) fpga_led_count++; // If SW7 is set (reads 1), count up
            else fpga_led_count--; // Count down
            *fpga_addr_8bit = fpga_led_count; // Write LED count
            for(loop_count = 0; loop_count < COUNTER_DELAY; loop_count++){}; // Delay
        }
        else if(fpga_value_8bit & SW1_MASK) // If SW1 is set (reads 1)
        {
            //fpga_value_8bit = *fpga_addr_8bit;
            *fpga_addr_8bit = fpga_value_8bit;
            //*fpga_addr_8bit = *fpga_addr_8bit; 
            for(loop_count = 0; loop_count < COUNTER_DELAY; loop_count++){}; // Delay
        }
        else
        {
            *fpga_addr_8bit = fpga_led_count; // Display frozen counter
            for(loop_count = 0; loop_count < COUNTER_DELAY; loop_count++){}; // Delay
        }
        // End Part 8 --------------------------------------------------------------------------------
        */
        /*
        // Part 9 - Timing tests ---------------------------------------------------------------------
        fpga_addr_8bit = (uint8_t *) FPGA_ADDR_CS3; // Store KSEG3 address
        *fpga_addr_8bit = 0x00; // Write all zeros
        fpga_value_8bit = *fpga_addr_8bit; // Read all ones
        fpga_value_8bit = 0; // Set breakpoint
        *fpga_addr_8bit = 0x00; // Write all zeros
        *fpga_addr_8bit = 0xFF; // Write all ones
        *fpga_addr_8bit = 0x00; // Write all zeros
        fpga_value_8bit = 0; // Set breakpoint
        // End Part 9 --------------------------------------------------------------------------------
        */
        // Part 10 - Invert test ---------------------------------------------------------------------
        fpga_addr_8bit = (uint8_t *) FPGA_ADDR_CS3; // Store KSEG3 address
        *fpga_addr_8bit = 0xA5; // 0b10100101
        for(loop_count = 0; loop_count < COUNTER_DELAY; loop_count++){}; // Delay
        fpga_addr_8bit = (uint8_t *) FPGA_INV_ADDR_CS3; // Store KSEG3 address
        *fpga_addr_8bit = 0xF0; // Invert 4 MSBs
        for(loop_count = 0; loop_count < COUNTER_DELAY; loop_count++){}; // Delay
        // End Part 10 -------------------------------------------------------------------------------
    }
    return (1);
}