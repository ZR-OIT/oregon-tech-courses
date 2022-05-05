/* Zak Rowland - 10/25/2018
   Lab 5 - Using a stack frame */
    
#include <p32xxxx.h>
.global main
.set noreorder

#define total_count 56 //total_count is at offset 56 in the stack frame
#define var_count 16 //var_count starts at offset 16 in the stack frame
   
.macro PUSH reg //Macro to push a character onto the stack
    addiu sp, sp, -4
    sw \reg, 0(sp)
.endm
    
.macro POP reg //Macro to pop a character off the stack
    lw \reg, 0(sp)
    addiu sp, sp, 4
.endm
    
.data
my_string: .asciiz "12345678911223344556654659685807548274058972074508"
Numof:    .asciiz "The number of _s is: "
Numdig:	  .asciiz "The total number of digits is: "
CrLf:     .asciiz "\n\r"
Numstr:   .space 11   // space for up to 10 ascii digit characters and a null

.text
    
.ent main
/********************
    Stack Frame
 ====Reg Save Area====
 ra		72
 old fp		68
 s0		64
 s1		60
 =====Local Vars=====
 total_count	56
 var_count array 52-16
 ===Parameter Space===
 res a3		12
 res a2		8
 res a1		4
 res a0		0
 ********************/
/*************************************************************************
Function: main
Purpose: Controls the process of counting, converting, and outputting.
Arguments: s0 holds the address of my_string, s1 holds an index count
	    starting at 0.
*************************************************************************/
main:
    // configure Uart1 for TX
     li   t0, 0x8000
     sw   t0, U1MODESET // Turn UART1 ON
     li   t0, 0x1400
     sw   t0, U1STASET  // Enable Receive and Transmit
    // done configuring UART1
    
    // Stack Frame setup ///////
    addiu sp, sp, -76
    sw ra, 72(sp)
    sw fp, 68(sp)
    addu fp,$0,sp //fp = sp
    sw s0, 64(fp)
    sw s1, 60(fp)
    sw zero, total_count(fp)
    sw zero, var_count + 36(fp)
    sw zero, var_count + 32(fp)
    sw zero, var_count + 28(fp)
    sw zero, var_count + 24(fp)
    sw zero, var_count + 20(fp)
    sw zero, var_count + 16(fp)
    sw zero, var_count + 12(fp)
    sw zero, var_count + 8(fp)
    sw zero, var_count + 4(fp)
    sw zero, var_count(fp)
    // Stack Frame done ///////
    
    la s0, my_string //loads address of string into register s0
    li s1, 0 //loads index of 0 into register s1
    lbu a0, 0(s0) //loads a character from string into register a0
    beq a0, $0, convert //if char is null skip to convert
    nop
begin:
    jal is_a_digit //jumps to is_a_digit subroutine
    nop
    bltz v0, skip //if -1 is returned skip to next char
    nop
    
    addiu t0, fp, var_count //t0 gets the address of the base of the variable array
    sll v0, v0, 2 //multiply the index by 4 (4 bytes per word)
    addu t0, t0, v0 //t0 gets the address of the indexed element
    lw v0, 0(t0) //get the value of the element
    addiu v0, v0, 1 //increment by 1
    sw v0, 0(t0) //store back onto stack
    
    lw v0, total_count(fp) //get the value of total_count
    addiu v0, v0, 1 //increment by 1
    sw v0, total_count(fp) //get the value of total_count
skip:
    addiu s0, s0, 1 //points to next char
    lbu a0, 0(s0) //loads a character from string into register a0
    bne a0, $0, begin //if char isn't null loop to beginning
    nop
convert:
    addiu t0, s1, 0x30 //loads the index value from s1 into t0
    sb t0, 14+Numof //stores converted value into the _ of Numof
    
    la a0, Numof //loads a pointer to Numof into a0
    jal output_string //outputs the Numof string
    nop
    
    addiu t0, fp, var_count //t0 gets the base address of array
    addu t1, $0, s1 //t1 gets the current index value from s0
    sll t1, t1, 2 //multiply index by 4
    addu t0, t0, t1 //t0 gets address of indexed element
    lw a0, 0(t0) //a0 gets the value of the indexed element
    la a1, Numstr //loads a pointer to Numstr into a1
    jal bin_to_asciidec //converts array value into ascii
    nop
    
    la a0, Numstr //loads a pointer to Numstr into a0 
    jal output_string //outputs the Numstr
    nop
    
    la a0, CrLf //loads a pointer to the carriage return and line feed string
    jal output_string //outputs the carriage return and line feed string
    nop
    
    addiu s1, s1, 1 //increment index counter
    li t0, 10 //loads 10 into t0
    bne t0, s1, convert //convert while s1 != 10
    nop
    li s1, 0 //reset s1 to 0
main_done:
    la a0, Numdig //loads a pointer to Numdig into a0
    jal output_string //outputs the Numof string
    nop
    lw a0, total_count(fp) //a0 gets the total_count
    la a1, Numstr //loads a pointer to Numstr into a1
    jal bin_to_asciidec //converts array value into ascii
    nop
    la a0, Numstr //loads a pointer to Numstr into a0 
    jal output_string //outputs the Numstr
    nop
    la a0, CrLf //loads a pointer to the carriage return and line feed string
    jal output_string //outputs the carriage return and line feed string
    nop
    
    lw ra, 72(sp)
    lw fp, 68(sp)
    lw s0, 64(sp)
    lw s1, 60(sp)
    addiu sp, sp, 76
    
    j .
    nop
.end main
    
.ent bin_to_asciidec
/*************************************************************************
Function: bin_to_asciidec
Purpose: Converts a binary number into an ascii decimal string
	    representation of that number.
Arguments: A 32-bit unsigned decimal value in register a0, and a pointer
	    to an 11 byte space in the .data segment in register a1.
*************************************************************************/
bin_to_asciidec:
    li t0, 0x0 //Load a null character
    PUSH t0 //Push null character onto stack
ascii_convert:
    li t1, 10 //Loads decimal 10 into register t1
    divu $0, a0, t1 //Divide by 10
    mfhi t2 //Move remainder to t2
    addiu t2, t2, 0x30 //Convert to ascii decimal by adding 0x30
    PUSH t2 //Pushes converted value onto stack
    mflo a0 //Moves the quotient into t0
    bne a0, $0, ascii_convert //If quotient is not 0, division is not done
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
    
.ent is_a_digit
/*************************************************************************
Function: is_a_digit
Purpose: Tests if a character from a string is a digit.
Arguments: a0 holds a byte (character) and v0 returns a -1 if not a digit,
	    or the value of the digit if it is a number.
*************************************************************************/
is_a_digit:
    li v0, -1 //loads -1 into v0
    li t0, 0x39 //loads 0x39 into register t0
    bgt a0, t0, not //char is not a digit if greater than 0x39
    nop
    li t0, 0x30 //initializes register t0 to 0x30 (0)
    blt a0, t0, not //char is not a digit if less than 0
    nop
    subu v0, a0, t0 //subtracts 0x30 from char to find its value
not:
    jr ra
    nop
.end is_a_digit    
   
.ent output_string
/*************************************************************************
Function: output_string
Purpose: Sends a string to UART1.
Arguments: A pointer to the string to output is passed in a0, and 
	    nothing is returned.
*************************************************************************/
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