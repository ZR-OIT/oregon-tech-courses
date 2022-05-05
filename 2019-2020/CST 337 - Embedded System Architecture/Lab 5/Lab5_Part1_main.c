/*******************************************************************************
* Name: Zak Rowland
* Date: 11/4/2019
* Lab: 5
* Description: SPI Interface with the 25LC256
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

#define SPI_READ 0x03 //SPI read command
#define SPI_WRITE 0x02 //SPI write command
#define SPI_WRDI 0x04 //SPI write disable command
#define SPI_WREN 0x06 //SPI write enable command
#define SPI_RDSR 0x05 //SPI read status command
#define SPI_DUMMY 0xFF //Dummy data for SPI

#include <xc.h>
#include <string.h>
#include <sys/attribs.h>

void InitializeSPI(void);
uint8_t ReadStatus(void);
void WriteEnable(void);
void WriteDisable(void);
void Write(uint16_t base_address, uint8_t num_of_bytes, uint8_t * data);
void Read(uint16_t base_address, uint8_t num_of_bytes, uint8_t * data);

int main()
{
	uint8_t data_buffer[64] = {0};
    uint8_t returned_data = 0;
    uint8_t write_small_int = 15;
    int write_big_int = 2146000000;
    char write_char = 'Z';
    char write_string[] = "Test string!";
    
    PRECON = (1 & _PRECON_PFMWS_MASK) | ((2 << _PRECON_PREFEN_POSITION) & _PRECON_PREFEN_MASK); //Change wait state value to 1 and enable prefetch
    
    SYSKEY = 0; //Ensure lock
    SYSKEY = 0xAA996655; //Write key 1
    SYSKEY = 0x556699AA; //Write key 2
    PB2DIV = _PB2DIV_ON_MASK | 0 & _PB2DIV_PBDIV_MASK; //0 = div by 1 (PBCLK2 = 84MHz)
    SYSKEY = 0; //Ensure lock
    
    InitializeSPI(); //Setup SPI
   
    //returned_data = ReadStatus();
    //WriteDisable();
    //returned_data = ReadStatus();
    //WriteEnable();
    //returned_data = ReadStatus();
    
	Write(0xF0F0, sizeof(write_small_int), &write_small_int); //Write 1 byte integer
    Read(0xF0F0, sizeof(write_small_int), data_buffer);
    memset(data_buffer, 0, sizeof(data_buffer)); //Clear buffer
    
    write_small_int = 10;
    Write(0x0000, sizeof(write_small_int), &write_small_int); //Write different 1 byte integer
    Read(0x0000, sizeof(write_small_int), data_buffer);
    memset(data_buffer, 0, sizeof(data_buffer)); //Clear buffer
    
    Write(0x0000, sizeof(write_big_int), (uint8_t *)&write_big_int); //Write 4 byte integer
    Read(0x0000, sizeof(write_big_int), data_buffer);
    memset(data_buffer, 0, sizeof(data_buffer)); //Clear buffer
    
    Write(0x0200, sizeof(write_char), (uint8_t *)&write_char); //Write 1 byte char
    Read(0x0200, sizeof(write_char), data_buffer);
    memset(data_buffer, 0, sizeof(data_buffer)); //Clear buffer
    
    Write(0x0400, sizeof(write_string), (uint8_t *)&write_string); //Write multi-byte string
    Read(0x0400, sizeof(write_string), data_buffer);
    memset(data_buffer, 0, sizeof(data_buffer)); //Clear buffer
    
    Read(0x405, 7, data_buffer); //string!
    memset(data_buffer, 0, sizeof(data_buffer)); //Clear buffer
    
    while(1){}
    
    return 0;
}

void InitializeSPI(void)
{
    SPI4CON = 0x0; //Stops and resets SPI4
    SPI4BUF; //Clears the receive buffer
    ANSELBCLR = _ANSELB_ANSB3_MASK; //Clear bit 3 in ANSELB to make RPB3 digital only
    TRISBSET = _TRISB_TRISB3_MASK; //Set bit 3 in TRISB to make SDI4 an input
    SDI4R = 0x8; //SDI4 is connected to RPB3
    RPF2R = 0x8; //SDO4 is connected to RPF2
    LATFSET = _LATF_LATF8_MASK; //Set bit 8 in LATF to leave the 25LC256 unselected
    TRISFCLR = _TRISF_TRISF8_MASK; //Clear bit 8 in TRISF to control CS (LATF8)
    SPI4BRG = 8; //BRG = 8, PBclk = 84MHz, SPICLK = 4.6666MHz
    //SPI4BRG = 20; //BRG = 20, PBclk = 84MHz, SPICLK = 2MHz
	//CKE (bit 8) = 0, SMP (bit 9) = 0, MSSEN (bit 28) = 0 in SPI4CON
	SPI4CON = _SPI4CON_MSTEN_MASK | _SPI4CON_CKP_MASK; //MSTEN (bit 5) = 1, CKP (bit 6) = 1, 8 bit mode
    SPI4CONSET = _SPI4CON_ON_MASK; //Turn on SPI4
}

uint8_t ReadStatus(void)
{
    uint8_t returned_data = 0;
    LATFCLR = _LATF_LATF8_MASK; //Assert CS (LATF8)
    SPI4BUF = SPI_RDSR; //Write a read status command to the 25LC256
    while(SPI4STATbits.SPITBE == 0){} //Wait for Transmit Buffer Empty (TBE = 1)
    SPI4BUF = SPI_DUMMY; //Write a dummy data byte
    while(SPI4STATbits.SPIRBF == 0){} //Wait for Receive Buffer Full (RBF = 1)
    SPI4BUF; //Read and discard the dummy data that was clocked in
    while(SPI4STATbits.SPIRBF == 0){} //Wait for Receive Buffer Full (RBF = 1)
    returned_data = SPI4BUF; //Read the status byte
    LATFSET = _LATF_LATF8_MASK; //Negate CS
    return returned_data;
}

void WriteEnable(void)
{
    LATFCLR = _LATF_LATF8_MASK; //Assert CS (LATF8)
    SPI4BUF = SPI_WREN; //Write a write enable command to the 25LC256
    while(SPI4STATbits.SPIRBF == 0){} //Wait for Receive Buffer Full (RBF = 1)
    SPI4BUF; //Read and discard the dummy data that was clocked in
    LATFSET = _LATF_LATF8_MASK; //Negate CS
}

void WriteDisable(void)
{
    LATFCLR = _LATF_LATF8_MASK; //Assert CS (LATF8)
    SPI4BUF = SPI_WRDI; //Write a write disable command to the 25LC256
    while(SPI4STATbits.SPIRBF == 0){} //Wait for Receive Buffer Full (RBF = 1)
    SPI4BUF; //Read and discard the dummy data that was clocked in
    LATFSET = _LATF_LATF8_MASK; //Negate CS
}

void Write(uint16_t base_address, uint8_t num_of_bytes, uint8_t * data)
{
    uint16_t i = 0;
    while(ReadStatus() & 0x01){} //Wait for write in progress
    WriteEnable();
    LATFCLR = _LATF_LATF8_MASK; //Assert CS (LATF8)
    SPI4BUF = SPI_WRITE; //Write a write command to the 25LC256
    while(SPI4STATbits.SPITBE == 0); //Wait for Transmit Buffer Empty (TBE = 1)
    SPI4BUF = base_address >> 8; //Write MSA to the 25LC256
    while(SPI4STATbits.SPIRBF == 0); //Wait for Receive Buffer Full (RBF = 1)
    SPI4BUF; //Read and discard the dummy data that was clocked in
    SPI4BUF = base_address; //Write LSA to the 25LC256
    while(SPI4STATbits.SPIRBF == 0){} //Wait for Receive Buffer Full (RBF = 1)
    SPI4BUF; //Read and discard the dummy data that was clocked in
    for(i = 0; i < num_of_bytes; i++)
    {
        SPI4BUF = *data; //Write data to the 25LC256
        while(SPI4STATbits.SPIRBF == 0){} //Wait for Receive Buffer Full (RBF = 1)  
        SPI4BUF; //Read and discard the dummy data that was clocked in
        data++; //Increment data pointer
    }
    while(SPI4STATbits.SPIRBF == 0){} //Wait for Receive Buffer Full (RBF = 1)  
    SPI4BUF; //Read and discard the dummy data that was clocked in  
    LATFSET = _LATF_LATF8_MASK; //Negate CS
}

void Read(uint16_t base_address, uint8_t num_of_bytes, uint8_t * data)
{
    uint16_t i = 0;
    uint8_t temp = 0;
    while(ReadStatus() & 0x01){} //Wait for write in progress
    LATFCLR = _LATF_LATF8_MASK; //Assert CS (LATF8)
    SPI4BUF = SPI_READ; //Write a read command to the 25LC256
    while(SPI4STATbits.SPITBE == 0){} //Wait for Transmit Buffer Empty (TBE = 1)
    SPI4BUF = base_address >> 8; //Write MSA to the 25LC256
    while(SPI4STATbits.SPIRBF == 0){} //Wait for Receive Buffer Full (RBF = 1)
    SPI4BUF; //Read and discard the dummy data that was clocked in
    SPI4BUF = base_address; //Write LSA to the 25LC256
    while(SPI4STATbits.SPIRBF == 0){} //Wait for Receive Buffer Full (RBF = 1)
    for(i = 0; i < num_of_bytes + 1 ; i++)
    {
        temp = SPI4BUF; //Temporarily store the data from the buffer
        if(i < num_of_bytes) SPI4BUF = SPI_DUMMY; //Output a dummy byte for every byte of data read
        if(i > 1)
            *data++ = temp; //Read data from the 25LC256
        while(SPI4STATbits.SPIRBF == 0){} //Wait for Receive Buffer Full (RBF = 1)
        *data = SPI4BUF;
    }
    LATFSET = _LATF_LATF8_MASK; //Negate CS
}