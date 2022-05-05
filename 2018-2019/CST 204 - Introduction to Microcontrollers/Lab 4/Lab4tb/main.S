////////////////////////////////////////////////////////////////////////////////
// File:	main.S
// 
// Lab:		lab4ta
////////////////////////////////////////////////////////////////////////////////

#include <xc.h>

.global main

.text
.set noreorder

.ent main
// main: Stack frame: {{{
//		[Register save]
//	ra		20
//	fp		16
//		[Parameter space]
//	a3		12
//	a2		8
//	a1		4
//	a0		0
////////////////////////////////////////////////////////////////////////////////
	main:
//create stack
addiu	sp,sp,-24
sw	ra,20(sp)
sw	fp,16(sp)
move	fp,sp

// clear timer1 configuration
la	v1,	T1CON
li	v0,	0x00
sw	v0,	0(v1)

// clear timer1 interrupt flag
la	v1,	IFS0CLR
li	v0,	0x10
sw	v0,	0(v1)

la	v1,	T1CONSET
li	v0,	0x10
sw	v0,	0(v1)
 
la	v1,	SYSKEY
li	v0,	0x0
sw	v0,	0(v1) 
    la	v1,	SYSKEY
li	v0,	0xaa996655
sw	v0,	0(v1) 
    la	v1,	SYSKEY
li	v0,	0x556699aa
sw	v0,	0(v1) 
    
la	v1,	OSCCONCLR
li	v0,	0x180000
sw	v0,	0(v1) 
    
la	v1,	OSCCONSET
li	v0,	0x100000
sw	v0,	0(v1)  
    
la	v1,	SYSKEY
li	v0,	0x0
sw	v0,	0(v1)        

/*la		v1,		LATASET
li		v0,		0x5A
sw		v0,		0(v1)*/

// set PORTA pins to non-open drain
la		v1,		ODCACLR
li		v0,		0xFF
sw		v0,		0(v1)

// set PORTA pins to output
la		v1,		TRISACLR
li		v0,		0xFF
sw		v0,		0(v1)
 
// clear PORTA pins to a known state
la	v1,		PORTACLR//initialize PORTA to 0x00 
li	v0,		0xff
sw	v0,		0(v1)

// set PORTA's LEDs to the 0x5A state
la		v1,		PORTASET
li		v0,		0x5A
sw		v0,		0(v1)

//start of loop
//invert state of PORTA's LEDs
	loop:
la		v1,		PORTAINV
li		v0,		0xFF
sw		v0,		0(v1)

// set delay count and jump to delay subroutine four times
// it takes 0.125 seconds to go thru each timer1_delay_call
// so a given LED pattern will be on for 1/2 second and 
// then it will change to the other LED pattern
li		a0,		62500
jal timer1_delay_1
nop

j	loop
nop

// Stack return
move	fp,		sp
lw		ra,		20(sp)
lw		fp,		16(sp)
addiu	sp,	sp,		24// Restore stack

// }}}
.end main


////////////////////////////////////////////////////////
// Wait 
// Parameters:
//		a0: delay parameter
//
// Returns:
///////////////////////////////////////////////////////
.ent timer1_delay_1
	timer1_delay_1: // {{{

// Clear timer 1 count value - start counting from zero
la		v1,		TMR1
li		v0,		0x0000
sw		v0,		0(v1)

// Load period target register
la		v1,		PR1
sw		a0,		0(v1)

// Turn clock on bit 15 = ON
la		v1,		T1CONSET
li		v0,		0x8000
sw		v0,		0(v1)

	timer1_loop:
// Read T1IF <4>
la		v1,		IFS0
lw		v1,		0(v1)
andi	v1,	v1,	0x10// Mask to 4th bit

beq	v1,	$0,	timer1_loop
nop
//stop timer1 - clear T1CON<15>
la		v1,		T1CONCLR
li		v0,		0x8000
sw		v0,		0(v1)
//CLEAR interrupt status flag timer1
la		v1,		IFS0CLR
li		v0,		0x10
sw		v0,		0(v1)

	instr_end:
jr		ra
nop
// }}}
.end timer1_delay_1
