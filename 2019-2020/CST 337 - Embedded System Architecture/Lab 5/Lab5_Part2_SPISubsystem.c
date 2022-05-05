/*******************************************************************************
* Name: Zak Rowland
* Date: 11/25/2019
* Lab: 5
* Description: SPI Interface with the 25LC256
*******************************************************************************/
#define SPI_READ 0x03 //SPI read command
#define SPI_WRITE 0x02 //SPI write command
#define SPI_WRDI 0x04 //SPI write disable command
#define SPI_WREN 0x06 //SPI write enable command
#define SPI_RDSR 0x05 //SPI read status command
#define SPI_DUMMY 0xFF //Dummy data for SPI

#include <xc.h>
#include <sys/attribs.h>

int EEPromSysBusy;
static int EEPromNumBytes;
static int EEPromAddress;
static uint8_t* EEPromReadBuffer;
static uint8_t* EEPromWriteBuffer;
static int EEPromReadWrite;
static int EEPromState;
static int write_counter;
static int read_counter;
static uint8_t read_temp;

void __ISR_AT_VECTOR(_SPI4_RX_VECTOR, IPL7SRS) SpiServ(void)
{
	uint8_t returned_data = 0;
	switch(EEPromState)
	{
		case 0: //Start check status sequence
		    LATFCLR = _LATF_LATF8_MASK; //Assert CS (LATF8)
			SPI4BUF = SPI_RDSR; //Write a read status command to the 25LC256
			while(SPI4STATbits.SPITBE == 0){} //Wait for Transmit Buffer Empty (TBE = 1)
			SPI4BUF = SPI_DUMMY; //Write a dummy data byte
			EEPromState = 1; //Set state to 1
			break;
		case 1: //Mid check status sequence
			SPI4BUF; //Read and discard the dummy data that was clocked in
			EEPromState = 2; //set state to 2
			break;
		case 2: //End check status sequence, start read or write enable, or repeat check status
			returned_data = SPI4BUF; //Read status
			LATFSET = _LATF_LATF8_MASK; //Negate CS
			if(returned_data & 0x01) //Write still in progress, start check status sequence again
			{
				LATFCLR = _LATF_LATF8_MASK; //Assert CS (LATF8) !HERE!
				SPI4BUF = SPI_RDSR; //Write a read status command to the 25LC256
				while(SPI4STATbits.SPITBE == 0){} //Wait for Transmit Buffer Empty (TBE = 1)
				SPI4BUF = SPI_DUMMY; //Write a dummy data byte
				EEPromState = 1; //Set state to 1
			}
			else if(EEPromReadWrite == SPI_WRITE) //Start write sequence with write enable
			{
                write_counter = 0; //Reset counter
                LATFCLR = _LATF_LATF8_MASK; //Assert CS (LATF8)
				SPI4BUF = SPI_WREN; //Write a write enable command to the 25LC256
				EEPromState = 3; //Set state to 3
			}
			else //Start read sequence and write MSA
			{
				read_counter = 0; //Reset counter
                read_temp = 0; //Reset temp
                LATFCLR = _LATF_LATF8_MASK; //Assert CS (LATF8)
                SPI4BUF = SPI_READ; //Write a read command to the 25LC256
                while(SPI4STATbits.SPITBE == 0){} //Wait for Transmit Buffer Empty (TBE = 1)
                SPI4BUF = EEPromAddress >> 8; //Write MSA to the 25LC256
                EEPromState = 7; //Set state to 7
			}
            break;
        case 3: //End write enable, start write sequence and write MSA
			SPI4BUF; //Read and discard the dummy data that was clocked in
			LATFSET = _LATF_LATF8_MASK; //Negate CS
			asm volatile("nop"); //Must be 5+ cycles between negate and assert
            asm volatile("nop"); //Must be 5+ cycles between negate and assert
            asm volatile("nop"); //Must be 5+ cycles between negate and assert
            LATFCLR = _LATF_LATF8_MASK; //Assert CS (LATF8) !HERE!
			SPI4BUF = SPI_WRITE; //Write a write command to the 25LC256
			while(SPI4STATbits.SPITBE == 0){} //Wait for Transmit Buffer Empty (TBE = 1)
			SPI4BUF = EEPromAddress >> 8; //Write MSA to the 25LC256
			EEPromState = 4; //Set state to 4
            break;
		case 4: //Continue write sequence, write LSA
            SPI4BUF; //Read and discard the dummy data that was clocked in
            SPI4BUF = EEPromAddress; //Write LSA to the 25LC256
            EEPromState = 5; //Set state to 5
            break;
        case 5: //Continue write sequence, write data
            SPI4BUF; //Read and discard the dummy data that was clocked in
            if(write_counter < EEPromNumBytes) //Write a byte
            {
                SPI4BUF = *EEPromWriteBuffer; //Write data to the 25LC256
                write_counter++; //Increment the counter
                if(write_counter < EEPromNumBytes) EEPromWriteBuffer++; //Increment data buffer pointer
                EEPromState = 5; //Set state to 5
            }
            else EEPromState = 6; //Done, set state to 6
            break;
        case 6: //Finish write sequence
            SPI4BUF; //Read and discard the dummy data that was clocked in
            LATFSET = _LATF_LATF8_MASK; //Negate CS
            EEPromSysBusy = 0; //No longer busy
            EEPromState = 0; //Restart state machine
            break;
        case 7: //Continue read sequence, write LSA
            SPI4BUF; //Read and discard the dummy data that was clocked in
            SPI4BUF = EEPromAddress; //Write LSA to the 25LC256
            EEPromState = 8; //Set state to 8
            break;
        case 8: //Continue read sequence, read data
            if(read_counter < EEPromNumBytes + 1)
            {
                read_temp = SPI4BUF; //Temporarily store the data from the buffer
                if(read_counter < EEPromNumBytes) SPI4BUF = SPI_DUMMY; //Output a dummy byte for every byte of data read
                if(read_counter > 1) *EEPromReadBuffer++ = read_temp; //Store data from the 25LC256
                read_counter++; //Increment counter
                EEPromState = 9; //Set state to 9
            }
            else EEPromState = 10; //Done, set state to 10
            break;
        case 9: //Continue read sequence, read data
            *EEPromReadBuffer = SPI4BUF; //Store data from the 25LC256
            if(read_counter < EEPromNumBytes + 1)
            {
                read_temp = SPI4BUF; //Temporarily store the data from the buffer
                if(read_counter < EEPromNumBytes) SPI4BUF = SPI_DUMMY; //Output a dummy byte for every byte of data read
                if(read_counter > 1) *EEPromReadBuffer++ = read_temp; //Store data from the 25LC256
                read_counter++; //Increment counter
                if(read_counter < EEPromNumBytes + 1) EEPromState = 9; //Continue reading, set state to 9
                else EEPromState = 10; //Done, set state to 10
            }
            else EEPromState = 10; //Done, set state to 10
            break;
        case 10: //Finish read sequence
            *EEPromReadBuffer = SPI4BUF; //Store data from the 25LC256
            LATFSET = _LATF_LATF8_MASK; //Negate CS
            EEPromSysBusy = 0; //No longer busy
            EEPromState = 0; //Restart state machine
            break;
        default:
            break;
	}
	IFS5CLR = _IFS5_SPI4RXIF_MASK; //Clear the SPI4RX interrupt flag
}

void ReadEEProm(int nbytes, unsigned int eeprom_address, uint8_t* readbuffer)
{
	while(EEPromSysBusy == 1){} //Wait for busy to be 0
	if(EEPromState != 0) exit(1); //If state is not 0 report an error
	EEPromSysBusy = 1; //Set busy
	EEPromNumBytes = nbytes;
	EEPromAddress = eeprom_address;
	EEPromReadBuffer = readbuffer;
	EEPromReadWrite = SPI_READ; //Indicate a read command
    LATHINV = _PORTH_RH8_MASK; //Toggle LED
	IFS5SET = _IFS5_SPI4RXIF_MASK; //Set SPIxRXIF to start things up, bit 4 in IFS5
}

void WriteEEProm(int nbytes, unsigned int eeprom_address, uint8_t* writebuffer)
{
	while(EEPromSysBusy == 1){} //Wait for busy to be 0
	if(EEPromState != 0) exit(1); //If state is not 0 report an error
	EEPromSysBusy = 1; //Set busy
	EEPromNumBytes = nbytes;
	EEPromAddress = eeprom_address;
	EEPromWriteBuffer = writebuffer;
	EEPromReadWrite = SPI_WRITE; //Indicate a write command
	IFS5SET = _IFS5_SPI4RXIF_MASK; //Set SPIxRXIF to start things up, bit 4 in IFS5
}