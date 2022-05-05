/*********************************************************************
 *
 *         Main function
 *
 *********************************************************************
 * FileName:        all_code.S
 *
 * Student name:    demo code
 ********************************************************************/

#include <xc.h>

#define bit_T1_ON	0x8000
#define bit_T1IF	0x0010

/* define all global symbols here */
.global lcd_init_pins
.global lcd_config
.global uart_config
.global lcd_write_string
.global uart_send_byte
.global timer1_delay

.text
.set noreorder


////////////////////////////////////////////////////////////////////////////
// Function lcd_config
//
//    Receives: nothing
//    Returns: nothing
//
//    Calls: lcd_write_comm_addr
//    Sends: a0 - command code
//
// This function configures the LCD module with the following settings:
//    Function set:    (0x38) 8-bit data length/2-line display/5x8 character font
//    Entry Mode set:  (0x06) Increment DDRAM address/No display shift
//    Display Control: (0x0f) Display On/Cursor on/Cursor blink on
////////////////////////////////////////////////////////////////////////////
.ent lcd_config
lcd_config:
		// construct stack frame
		addiu	sp, sp, -24
		sw		ra, 20(sp)
		sw		fp, 16(sp)
		move	fp, sp

		// Initialize the LCD module
		li		a0, 0x0038			// set Function 8-bit/2 line/5x8 dots
		jal		lcd_write_comm_addr	// set Function 8-bit/2 line/5x8 dots
		nop							// set Function 8-bit/2 line/5x8 dots

		li		a0, 0x0006			// set Entry Mode increment/NO shift
		jal		lcd_write_comm_addr	// set Entry Mode increment/NO shift
		nop							// set Entry Mode increment/NO shift

		li		a0, 0x000f			// set Display ON/Cursur ON/ Blink ON
		jal		lcd_write_comm_addr	// set Display ON/Cursur ON/ Blink ON
		nop							// set Display ON/Cursur ON/ Blink ON

		// release stack frame
		move	sp, fp
		lw		ra, 20(sp)
		lw		fp, 16(sp)
		addiu	sp, sp, 24

		jr		ra
		nop

.end lcd_config


////////////////////////////////////////////////////////////////////////////
// Function lcd_init_pins
//
//    Receives: nothing
//    Returns: nothing
//
//    Calls: nothing
//    Sends: nothing
//
// The LCD module is wired to the PIC32 through the following pins:
//    RS - RB15: Configure to Output/non-Open drain, value = 0
//    RW - RD5:  Configure to Output/non-Open drain, value = 0
//    E  - RD4:  Configure to Output/non-Open drain, value = 0
//    D7_D0 - RE7-RE0: Left alone as these pins start in HI-Z
//
//    Note: Set "data values" before configuring pin to OUTPUT so that the
//          pin presents the right value when it starts DRIVING.
////////////////////////////////////////////////////////////////////////////
.ent lcd_init_pins
lcd_init_pins:
		// consrtuct stack frame
		addiu	sp, sp, -8
		sw		ra, 4(sp)
		sw		fp, 0(sp)
		move	fp, sp


		// Initialize RB15 pin for LCD signal RS
		la		t0, LATBCLR		// For RS=RB15
		li		t1, 0x8000		// For RS=RB15
		sw		t1, 0(t0)		// For RS=RB15
		la		t0, TRISBCLR	// For RS=RB15
		li		t1, 0x8000		// For RS=RB15
		sw		t1, 0(t0)		// For RS=RB15
		la		t0, ODCBCLR		// For RS=RB15
		li		t1, 0x8000		// For RS=RB15
		sw		t1, 0(t0)		// For RS=RB15

		// Initialize RD5/RD4 pins for LCD signals RW and E
		la		t0, LATDCLR		// For RW=RD5 and E=RD4
		li		t1, 0x0030		// For RW=RD5 and E=RD4
		sw		t1, 0(t0)		// For RW=RD5 and E=RD4
		la		t0, TRISDCLR	// For RW=RD5 and E=RD4
		li		t1, 0x0030		// For RW=RD5 and E=RD4
		sw		t1, 0(t0)		// For RW=RD5 and E=RD4
		la		t0, ODCDCLR		// For RW=RD5 and E=RD4
		li		t1, 0x0030		// For RW=RD5 and E=RD4
		sw		t1, 0(t0)		// For RW=RD5 and E=RD4

		// release stack frame
		move	sp, fp
		lw		ra, 4(sp)
		lw		fp, 0(sp)
		addiu	sp, sp, 8

	jr		ra
	nop

.end lcd_init_pins


////////////////////////////////////////////////////////////////////////////
// Function lcd_write_comm_addr (Write instruction or address)
//
//    Receives: a0 - INSTRUCTION CODE or ADDRESS VALUE
//    Returns: nothing
//
//    Calls: nothing
//    Sends: nothing
//
// This function will write a command (instruction) or a DDRAM address to
// the LCD. The LCD requires that the RS signal be 0 and the data value is
// coded in such a way as to dictate to the LCD controller that an command
// versus an address is being written on the current cycle.
//
// Note:
//   1. It is assumed that RS = 0 upon entry
//   2. It is assumed that RW = 0 upon entry
//   3. Data is setup in the LATCH BEFORE DRIVING the pins in Port E
//
////////////////////////////////////////////////////////////////////////////
.ent lcd_write_comm_addr
lcd_write_comm_addr:
		// consrtuct stack frame
		addiu	sp, sp, -8
		sw		ra, 4(sp)
		sw		fp, 0(sp)
		move	fp, sp
		sw		a0, 8(fp)

// Note: At start of sequence, assumed that RW = 0 and RS = 0
// RS = 0 for writing an INSTRUCTION
// This is why RW and RS are not touched in this sequence

		// SETUP DATA IN LATCH
		// Clear the latch
		la		t0, LATECLR
		li		t1, 0x00ff
		sw		t1, 0(t0)

		// SETUP DATA IN LATCH
		// Set the RE7 to RE0 pins to the value in $a0
		la		t0, LATESET
		sw		a0, 0(t0)			// Data/Instr value received in $a0

		// Set E to 1
		la		t0, LATDSET
		li		t1, 0x0010
		sw		t1, 0(t0)

		// DRIVE DATA PINS - DATA ALREADY IN LATCH
		// Set the RE7 to RE0 port pins to output
		la		t0, TRISECLR
		li		t1, 0x00FF
		sw		t1, 0(t0)

		// Set E to 0
		la		t0, LATDCLR
		li		t1, 0x0010
		sw		t1, 0(t0)

		// Set the RE7 to RE0 port pins to input (hi-z)
		la		t0, TRISESET
		li		t1, 0x00FF
		sw		t1, 0(t0)

		// release stack frame
		move	sp, fp
		lw		ra, 4(sp)
		lw		fp, 0(sp)
		addiu	sp, sp, 8

		jr		ra
		nop

.end lcd_write_comm_addr


////////////////////////////////////////////////////////////////////////////
// Function lcd_write_data (Display a character)
//
//    Receives: a0 - CHARACTER VALUE
//    Returns: nothing
//
//    Calls: nothing
//    Sends: nothing
//
// This function  will write a character data value at the currenet DDRAM
// address.
//
// Note:
//   1. RS is returned to 0 upon exit
//   2. It is assumed that RW = 0 upon entry
//   3. Data is setup in the LATCH BEFORE DRIVING the pins in Port E
//
////////////////////////////////////////////////////////////////////////////
.ent lcd_write_data
lcd_write_data:
		// consrtuct stack frame
		addiu	sp, sp, -8
		sw		ra, 4(sp)
		sw		fp, 0(sp)
		move	fp, sp
		sw		a0, 8(fp)

		// Set RS to 1
		la		t0, LATBSET
		li		t1, 0x8000
		sw		t1, 0(t0)

		// SETUP DATA IN LATCH
		// Clear the latch
		la		t0, LATECLR
		li		t1, 0x00ff
		sw		t1, 0(t0)

		// SETUP DATA IN LATCH
		// Set the RE7 to RE0 pins to the value in $a0
		la		t0, LATESET
		sw		a0, 0(t0)

		// Set E to 1
		la		t0, LATDSET
		li		t1, 0x0010
		sw		t1, 0(t0)

		// DRIVE DATA PINS - DATA ALREADY IN LATCH
		// Set the RE7 to RE0 port pins to output
		la		t0, TRISECLR
		li		t1, 0x00ff
		sw		t1, 0(t0)

		// Set E to 1
		la		t0, LATDCLR
		li		t1, 0x0010
		sw		t1, 0(t0)

		// Set the RE7 to RE0 port pins to input (hi-z)
		la		t0, TRISESET
		li		t1, 0x00ff
		sw		t1, 0(t0)

		// Set RS to 0
		la		t0, LATBCLR
		li		t1, 0x8000
		sw		t1, 0(t0)

		// release stack frame
		move	sp, fp
		lw		ra, 4(sp)
		lw		fp, 0(sp)
		addiu	sp, sp, 8

		jr		ra
		nop

.end lcd_write_data


////////////////////////////////////////////////////////////////////////////
// Function lcd_write_string (Display a string)
//
//    Receives: a0 - DDRAM (Display Data RAM) ADDRESS in LCD
//              a1 - STRING ADDRESS in memory (label)
//    Returns: nothing
//
//    Calls: lcd_writ_comm_addr
//    sends: a0 - INSTRUCTION CODE or ADDRESS VALUE
//
//    Calls: lcd_write_data
//    Sends: a0 - CHARACTER VALUE
//
////////////////////////////////////////////////////////////////////////////
.ent lcd_write_string
lcd_write_string:
		// consrtuct stack frame
		addiu	sp, sp, -32
		sw		ra, 28(sp)
		sw		fp, 24(sp)
		sw		s1, 20(sp)
		sw		s0, 16(sp)				// not used right now
		move	fp, sp
		sw		a0, 32(fp)				// save ddram address
		sw		a1, 36(fp)				// save string address

		move	s1, a1

		lw		a0, 32(fp)				// set ddram address
		jal		lcd_write_comm_addr		// set ddram address
		nop

string_write:
		lb		t0, 0(s1)				// s1 is string pointer
		beq		t0, zero, string_done
		nop

		move	a0, t0
		jal		lcd_write_data
		nop

		addiu	s1, s1, 1		// advance string pointer
		j		string_write
		nop

string_done:
		// release stack frame
		move	sp, fp
		lw		ra, 28(sp)
		lw		fp, 24(sp)
		lw		s1, 20(sp)
		lw		s0, 16(sp)
		addiu	sp, sp, 32

		jr		ra
		nop

.end lcd_write_string
///////////////////
///////////////////

///////////////////
///////////////////
/////////////////////////////////////////
// timer1_delay
//
//	Receives: a0 - timer period value
//
/////////////////////////////////////////
.ent timer1_delay
timer1_delay:
		// consrtuct stack frame
		addiu	sp, sp, -8
		sw		ra, 4(sp)
		sw		fp, 0(sp)
		move	fp, sp
		sw		a0, 8(fp)

		la		t0, TMR1
		sw		zero, 0(t0)			// reset timer register value

		la		t0, PR1
		sw		a0, 0(t0)				// initialize period register

		la		t0, T1CONSET
		li		t1, bit_T1_ON
		sw		t1, 0(t0)				// start timer 1

check_T1IF:
		la		t0, IFS0
		lw		t1, 0(t0)
		andi	t1, t1, bit_T1IF		// wait for flag

		beq		t1, zero, check_T1IF
		nop

		la		t0, T1CONCLR
		li		t1, bit_T1_ON
		sw		t1, 0(	t0)

		la		t0, IFS0CLR
		li		t1, bit_T1IF
		sw		t1, 0(t0)

		// release stack frame
		move	sp, fp
		lw		ra, 4(sp)
		lw		fp, 0(sp)
		addiu	sp, sp, 8

		jr		ra
		nop

.end timer1_delay
///////////////////
///////////////////


///////////////////
///////////////////
////////////////////////////////////////////////////////////////////////////
// UART configuration
//
////////////////////////////////////////////////////////////////////////////
.ent uart_config
uart_config:
		// consrtuct stack frame
		addiu	sp, sp, -8
		sw		ra, 4(sp)
		sw		fp, 0(sp)
		move	fp, sp

		// Configure the U2TXD pin (RF5) as OUTPUT
		la		t0, TRISFCLR
		li		t1, 0x20
		sw		t1, 0(t0)

		// Configure /4 Baud Rate Gen
		la		t0, U2MODESET
		li		t1, 0x0008
		sw		t1, 0(t0)

		// Set baud rate gen reg
		la		t0, U2BRG
		li		t1, 12
		sw		t1, 0(t0)


		// Configure TX/RX
		la		t0, U2STA
		li		t1, 0x5400
		sw		t1, 0(t0)

		// Make transmitter available
		// Set U2TXIF = IFS1<10> = 1
		la		t0, IFS1
		li		t1, 0x0400
		sw		t1, 0(t0)

		// TURN ON UART!!!
		la		t0, U2MODESET	// U2MODE
		li		t1, 0x8000
		sw		t1, 0(t0)

		// release stack frame
		move	sp, fp
		lw		ra, 4(sp)
		lw		fp, 0(sp)
		addiu	sp, sp, 8

		jr		ra
		nop

.end uart_config

/////////////////////////////////////////
// uart_send_byte
//
//	Receives: a0 - character value
//
/////////////////////////////////////////
.ent uart_send_byte
uart_send_byte:
		// consrtuct stack frame
		addiu	sp, sp, -8
		sw		ra, 4(sp)
		sw		fp, 0(sp)
		move	fp, sp
		sw		a0, 8(fp)

		la		t0, IFS1
wait_for_txif_1:
		lw		t1, 0(t0)			// read transmit flag
		andi	t1,	t1, 0x0400	// mask to U2TXIF bit
		beq		t1, zero, wait_for_txif_1
		nop

		// CLEAR U2TXIF
		la		t0, IFS1CLR
		li		t1, 0x0400			// bit 10
		sw		t1, 0(t0)			// clear U2TXIF flag

		la		t0, U2TXREG
		sw		a0, 0(t0)			// send TXD value

		// release stack frame
		move	sp, fp
		lw		ra, 4(sp)
		lw		fp, 0(sp)
		addiu	sp, sp, 8

		jr		ra
		nop

.end uart_send_byte
