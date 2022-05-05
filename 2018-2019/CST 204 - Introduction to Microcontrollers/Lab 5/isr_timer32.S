////////////////////////////////////////////////////////////////////////////////
// File:	isr_timer32.S
// Lab:		5
////////////////////////////////////////////////////////////////////////////////

#include <xc.h>

.global isr_timer32

.text
.set	noreorder

.ent isr_timer32
	isr_timer32: // {{{
// -------------------------Start of Prologue--------------------------------------
// Note: Upon entry, interrupts are DISABLED! (via ERL or EXL)errror level or exception level bit part of _cp0_status
rdpgpr	sp,		sp//read previous group 
addiu	sp, 	sp, -76						// Allocate necessary stack space*

mfc0	k1, 	_CP0_EPC					// Read EPC Register into k1
sw		k1, 	0(sp)						// Push *1* EPC Register contents
mfc0	k1, 	_CP0_STATUS					// Read Status Register into k1
sw		k1, 	4(sp)						// Push *2* Status Register contents
mfc0	k0, 	_CP0_CAUSE					// Read Cause Register into k0
srl		k0, 	k0,			10				// Align RIPL to bit 0
ins		k1, 	k0,			10,			6	// Set priority threshold
ins		k1, 	zero,		1,			4	// UM = 0; ERL = 0; EXL = 0
mtc0	k1, 	_CP0_STATUS					// Reenable INTs!

sw		fp,		8(sp)						// Push *n* as necessary
move	fp,		sp

sw		v0,		28(fp)						// save v0 an v1 since they are used	
sw		v1,		32(fp)						// in this routine

//----------------------------End of Prologue------------------------------------------
   
la v0, T2CONCLR
li v1, 0x8000 //T2CON <15>
sw v1, 0(v0) //stop timer 2
    
la v0, IFS0CLR 
li v1, 0x1000 //IFSO<12>
sw v1, 0(v0) //clear T3IF
    
//check FLASHER
    
la		v1,		FLASHER
lw		v0,		0(v1)
beq		v0,		zero,	clear_RA6
nop
    
la v1, PORTAINV
li v0, 0b1000000
sw v0, 0(v1) //invert RA6
    
la v0, TMR2
li v1, 0x0
sw v1, 0(v0) //clear timer2
   
la v0, PR2
li v1, 625000
sw v1, 0(v0) //load period register, 250ms PBCLK = 2.5MHz
	
la v0, T2CONSET
li v1, 0x8000 //T2CON<15>
sw v1, 0(v0) //turn on timer 2
 
j t32_epilogue
nop
    
clear_RA6:
la v1, PORTACLR
li v0, 0b1000000
sw v0, 0(v1) //clear RA6 of PORTA
    
t32_epilogue:    
//----------------------------Start of Epilogue----------------------------------------

lw		v0,		28(fp)						//restore v0 an v1
lw		v1,		32(fp)

move	sp,		fp
lw		fp,		8(sp)

di											// disable interrupt
lw		k0,		0(sp)						// Pop ERPC Rregister into k0
mtc0	k0,		_CP0_EPC					// Restore ERP contents
lw		k0,		4(sp)						// Pop status register
mtc0	k0,		_CP0_STATUS					// Restore status contents
addiu	sp,		sp,		76					// Restore stack pointer

eret // }}}
.end isr_timer32

// ISR for vector 4 (Timer 1 target reached)
.section	.vector_12,		code
j		isr_timer32
nop