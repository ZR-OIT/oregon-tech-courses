/*********************************************************************
 *
 *         Main function
 *
 *********************************************************************
 * FileName:        main.S
 *
 * Student name:    demo code
 ********************************************************************/

#include <xc.h>

#define bit_T1_ON	0x8000
#define bit_T1IF	0x0010

.global main

.text
.set noreorder

////////////////////////////////////////////////////////////////////////////
// main
//
////////////////////////////////////////////////////////////////////////////
.ent main
main:
		// construct stack frame
		addiu	sp, sp, -24
		sw		ra, 20(sp)
		sw		fp, 16(sp)
		move	fp, sp

	// initialize lcd pins
	jal		lcd_init_pins
	nop

	// configure lcd
	jal		lcd_config
	nop

	// initialize UART
	jal		uart_config
	nop



	// display lcd message
	li		a0, 0x0080			// set character address = 00h
	la		a1, line1			// display "Tranmitting 0x55"
	jal		lcd_write_string
	nop

	li		a0, 0x00c0			// set character address = 40h
	la		a1, line2			// display "on Serial Port  "
	jal		lcd_write_string
	nop

//////
loop_forever:
	// send 0x55 out uart (1.042 ms per byte)
		li		a0, 0x55
		jal		uart_send_byte
		nop

	// delay 10 ms
		li		a0, 5000
		jal		timer1_delay		// debounce delay
		nop

next_byte:
		j		loop_forever
		nop
//////

		// release stack frame
		move	sp, fp
		lw		ra, 20(sp)
		lw		fp, 16(sp)
		addiu	sp, sp, 24

		jr		ra
		nop

.end main


line1:	.asciiz "Transmit 0x55   "
line2:	.asciiz "on Serial Port  "
