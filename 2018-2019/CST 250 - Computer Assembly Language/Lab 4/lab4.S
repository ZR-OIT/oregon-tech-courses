/* Zak Rowland - 10/18/2018 
   Lab 4 - Converting Binary to Ascii Decimal */

#include <p32xxxx.h>
.global main
.set noreorder

.macro PUSH reg //Macro to push a character onto the stack
    addiu sp, sp, -4
    sw \reg, 0(sp)
.endm
    
.macro POP reg //Macro to pop a character off the stack
    lw \reg, 0(sp)
    addiu sp, sp, 4
.endm
    
.data
Numbers: .word 3456789, 379, 0, 9, 103, 0xffffffff //binary numbers to convert
N: .word 6 //number of words to convert
CrLf: .asciiz "\n\r"
Numstr: .space 11 //space for up to 10 ascii characters and a null

.text
.align 2 // ensures the data before the code does not
        // cause it to become un-aligned.
	
/*************************************************************************
Function: main
Purpose: Controls the conversion process
Arguments: s0 holds the amount of numbers to convert, s1 holds a pointer
	    to the array of numbers
*************************************************************************/
.ent main
main:
    addiu sp, sp, -16
    sw ra, 12(sp)
    sw fp, 8(sp)
    sw s1, 4(sp)
    sw s0, 0(sp)
        
    // configure Uart1 for TX
     li   t0, 0x8000
     sw   t0, U1MODESET // Turn UART1 ON
     li   t0, 0x1400
     sw   t0, U1STASET  // Enable Receive and Transmit
    // done configuring UART1
    
    lw s0, N //loads the number of words to convert (N) into regiser s0 
    blez s0, main_done //if there are 0 words to convert branch to done
    nop
    la s1, Numbers //loads a pointer to Numbers into s1
convert:
    lw a0, 0(s1) //loads a value from Numbers into a0
    la a1, Numstr //loads a pointer to Numstr into a1
    jal bin_to_asciidec //converts Number to an ascii string
    nop
    la a0, Numstr //loads a pointer to Numstr into a0
    jal output_string //outputs the Numstr string
    nop
    la a0, CrLf //loads a pointer to the carriage return and line feed string
    jal output_string //outputs the carriage return and line feed string
    nop
    addiu s0, s0, -1 //subracts 1 from the count of Numbers
    addiu s1, s1, 4 //moves the Numbers pointer to the next Number
    bne s0, $0, convert
    nop
    
    lw ra, 12(sp)
    lw fp, 8(sp)
    lw s1, 4(sp)
    lw s0, 0(sp)
    addiu sp, sp, 16
main_done:
    j .
    nop
.end main

/*************************************************************************
Function: bin_to_asciidec
Purpose: Converts a binary number into an ascii decimal string
	    representation of that number.
Arguments: A 32-bit unsigned decimal value in register a0, and a pointer
	    to an 11 byte space in the .data segment in register a1.
*************************************************************************/
.ent bin_to_asciidec
bin_to_asciidec:
    li t0, 0x0 //Load a null character
    PUSH t0 //Push null character onto stack
    addu t0, $0, a0 //Places the pointer from a0 into t0
ascii_convert:
    li t1, 10 //Loads decimal 10 into register t1
    divu $0, t0, t1 //Divide by 10
    mfhi t2 //Move remainder to t2
    addiu t2, t2, 0x30 //Convert to ascii decimal by adding 0x30
    PUSH t2 //Pushes converted value onto stack
    mflo t0 //Moves the quotient into t0
    bne t0, $0, ascii_convert //If quotient is not 0, division is not done
    nop
string:
    POP t3 //Remove a character from the stack
    sb t3, 0(a1) //Stores a character into the 11 byte space
    addiu a1, a1, 1 //Move pointer to next space
    bne t3, $0, string //If character is not null, branch to top of loop
    nop
convert_done:
    jr ra
    nop
.end bin_to_asciidec
    
    
/*************************************************************************
Function: output_string
Purpose: Sends a string to UART1.
Arguments: A pointer to the string to output is passed in a0, and 
	    nothing is returned.
*************************************************************************/
.ent output_string
output_string: 
     lbu   t0, 0(a0)      // get first char
     beq   t0, zero, done // if it is null, we are done
     nop


send:   
     sw    t0, U1TXREG    // send data to Uart1

wait_tx:
     lw    t0, U1STA          // get Uart1 Status  
     andi  t0, t0, 0x100      // select TX done bit
     beq   t0, zero, wait_tx  // if done bit not set, wait
     nop

     addiu a0, a0, 1      // update pointer to next char
     lbu   t0, 0(a0)      // get next char
     bne   t0, zero, send // if it is not null, output it
     nop

done:
jr ra
nop
.end output_string
/*************************************************************************/