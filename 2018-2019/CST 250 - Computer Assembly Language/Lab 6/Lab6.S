/* Zak Rowland - 11/8/2018
   Lab 6 - Calculating Isqrt */
#include <p32xxxx.h>
.global main
.set noreorder

#define debug 0
    
.macro PUSH reg //Macro to push a character onto the stack
    addiu sp, sp, -4
    sw \reg, 0(sp)
.endm
    
.macro POP reg //Macro to pop a character off the stack
    lw \reg, 0(sp)
    addiu sp, sp, 4
.endm
    
.data
my_num:	   .asciiz "1088c"
errorno:    .word 0
error_one:  .asciiz "The string is empty or contains more than 10 digits, isqrt has been skipped."
error_two:  .asciiz "The string contains non-digit characters which have been ignored."
.if debug
Dbgstr:	  .asciiz "debug iteration: "
Guesstr:   .asciiz " guess: "
.endif
    
FinalStr1: .asciiz "The isqrt of "
FinalStr2: .asciiz " is "
FinalStr3: .asciiz ". Check: "
FinalStr4: .asciiz "^2 = "
FinalStr5: .asciiz ", "
FinalStr6: .asciiz "^2 = "
FinalStr7: .asciiz "."
    
CrLf:     .asciiz "\n\r"
Numstr:   .space 11   // space for up to 10 ascii digit characters and a null

.text
.ent main
/*********************
    Stack Frame
 ====Reg Save Area====
 ra		24		
 fp		20
 s0		16
 =====Local Vars=====

 ===Parameter Space===
 res a3		12
 res a2		8
 res a1		4
 res a0		0
 ********************/
/*************************************************************************
Function: main
Purpose: Controls other functions and outputs final string/answer
Arguments: s0 is the value returned from isqrt
*************************************************************************/
main:
    addiu sp, sp, -12
    sw ra, 8(sp)
    sw fp, 4(sp)
    sw s0, 0(sp)
    
    // configure Uart1 for TX
     li   t0, 0x8000
     sw   t0, U1MODESET // Turn UART1 ON
     li   t0, 0x1400
     sw   t0, U1STASET  // Enable Receive and Transmit
    // done configuring UART1
	
main_ascii:
    sw $0, errorno //sets error to 0 before calling routine
    la a0, my_num 
    jal asciidec_to_bin
    nop
    
    lw t0, errorno //loads the error value into t0
    
    beq t0, $0, main_sqrt //if 0 continue as normal
    nop
    
    li t1, 1
    beq t0, t1, main_error_one //if 1 output string and skip isqrt
    nop
    
    li t1, 2
    beq t0, t1, main_error_two //if 2 output string and continue
    nop
main_error_one:
    la a0, error_one
    jal output_string
    nop
    la a0, CrLf
    jal output_string
    nop
    j main_done
    nop
main_error_two:
    la a0, error_two
    jal output_string
    nop
    la a0, CrLf
    jal output_string
    nop
main_sqrt:
    addu a0, $0, v0
    jal isqrt
    nop
    
    addu s0, $0, v0
main_display: //This section outputs the final result string   
    la a0, FinalStr1
    jal output_string
    nop
    
    la a0, my_num
    jal output_string
    nop
    
    la a0, FinalStr2
    jal output_string
    nop
    
    addu a0, $0, s0
    la a1, Numstr
    jal bin_to_asciidec
    nop
    
    la a0, Numstr
    jal output_string
    nop
    
    la a0, FinalStr3
    jal output_string
    nop
    
    la a0, Numstr
    jal output_string
    nop
    
    la a0, FinalStr4
    jal output_string
    nop
    
    mult s0, s0
    mflo t0
    addu a0, $0, t0
    la a1, Numstr
    jal bin_to_asciidec
    nop
    
    la a0, Numstr
    jal output_string
    nop
    
    la a0, FinalStr5
    jal output_string
    nop
    
    addiu a0, s0, 1
    la a1, Numstr
    jal bin_to_asciidec
    nop
    
    la a0, Numstr
    jal output_string
    nop
    
    la a0, FinalStr6
    jal output_string
    nop
    
    addiu t0, s0, 1
    mult t0, t0
    mflo t0
    addu a0, $0, t0
    la a1, Numstr
    jal bin_to_asciidec
    nop
    
    la a0, Numstr
    jal output_string
    nop
    
    la a0, FinalStr7
    jal output_string
    nop
    
    la a0, CrLf
    jal output_string
    nop
	// Output done /////////////////////////
main_done:
    lw ra, 8(sp)
    lw fp, 4(sp)
    lw s0, 0(sp)
    addiu sp, sp, 12
    
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

.ent asciidec_to_bin
/*********************
    Stack Frame
 ====Reg Save Area====
 ra		32		
 fp		28
 s2		24
 s1		20
 s0		16
 =====Local Vars=====

 ===Parameter Space===
 res a3		12
 res a2		8
 res a1		4
 res a0		0
 ********************/
/*************************************************************************
Function: asciidec_to_bin
Purpose: Converts a ascii decimal string into the binary representation
	 of that number.
Arguments: The address of a string is passed through a0, and the 32bit binary
	    value is returned in v0.
*************************************************************************/
asciidec_to_bin:
    addiu sp, sp, -20
    sw ra, 16(sp)
    sw fp, 12(sp)
    sw s2, 8(sp)
    sw s1, 4(sp)
    sw s0, 0(sp)
    
    li t0, 1
    sw t0, errorno
    
    li s0, 0 //set result to 0
    addu s1, $0, a0 //copies address of string into s1
    li s2, 0 //set count to 0
    
    lbu a0, 0(s1) //loads a character from string into register a0
    beq a0, $0, bin_done //if char is null skip to bin_done
    nop
    sw $0, errorno
bin_convert:

    jal is_a_digit //jumps to is_a_digit subroutine
    nop
    bltz v0, non_digit //if -1 is returned skip to next char
    nop
    
    li t1, 10 //loads 10 into t1
    multu s0, t1 //multiplies result by 10
    mflo s0 //stores result into s0
    addu s0, s0, v0 //adds result to total value in s0
    
    addiu s2, s2, 1 //increments counter
    li t0, 11 
    beq s2, t0, over_ten //checks if counter is over 10
    nop
    
    bgez v0, bin_skip
    nop
non_digit:
    li t0, 2
    sw t0, errorno //non digit char found, errorno = 2
bin_skip:
    addiu s1, s1, 1 //points to next char
    lbu a0, 0(s1) //loads a character from string into register a0
    bne a0, $0, bin_convert //if char isn't null, loop
    nop
    j bin_done
    nop
over_ten:
    li t0, 1
    sw t0, errorno
bin_done:  
    addu v0, s0, $0 //copies result into v0
    lw ra, 16(sp)
    lw fp, 12(sp)
    lw s2, 8(sp)
    lw s1, 4(sp)
    lw s0, 0(sp)
    addiu sp, sp, 20
    
    jr ra
    nop
.end asciidec_to_bin
    
.ent isqrt
/*********************
    Stack Frame
 ====Reg Save Area====
 ra		36		
 fp		32
 s3		28
 s2		24
 s1		20
 s0		16
 =====Local Vars=====

 ===Parameter Space===
 res a3		12
 res a2		8
 res a1		4
 res a0		0
 ********************/
/*************************************************************************
Function: isqrt
Purpose: Computes the isqrt of a 32 bit unsigned integer value.
Arguments: A 32 bit unsigned integer value is passed through a0, and
	    the 32 bit unsigned integer result is returned through v0.
*************************************************************************/
isqrt:
    //s0 = original guess
    //s1 = original number
    //s2 = calculations
    //s3 = counter
    addiu sp, sp, -24
    sw ra, 20(sp)
    sw fp, 16(sp)
    sw s3, 12(sp)
    sw s2, 8(sp)
    sw s1, 4(sp)
    sw s0, 0(sp)
   
    addu v0, $0, $0 //initialize v0 to 0
    addu s0, $0, a0 //initialize s0 to passed num 
    addu s1, $0, a0 //initialize s1 to passed num 
    
    addiu t0, $0, 1
    bleu s0, t0, isqrt_done
    nop
    
    .if debug
    li s3, 1 //initialize s2 to 1 (count)
    .endif
    
    srl s0, s0, 1 //(t0 / 2) = guess
    
isqrt_loop:
    .if debug
	addu a0, $0, s3
	la a1, Numstr
	jal bin_to_asciidec
	nop
    
	la a0, Dbgstr //loads a pointer to Dbgstr into a0
	jal output_string //outputs the Dbgstr string
	nop
	
	la a0, Numstr
	jal output_string
	nop
    
	addu a0, $0, s0 //a0 gets the value of the first guess (s0)
	la a1, Numstr //loads a pointer to Numstr into a1
	jal bin_to_asciidec //converts guess into ascii
	nop
	
	la a0, Guesstr
	jal output_string
	nop
	
	la a0, Numstr
	jal output_string
	nop
    
	la a0, CrLf
	jal output_string
	nop
	
	addiu s3, s3, 1
    .endif
    
    addu t1, $0, s0 //t1 gets the previous guess from s0
    divu $0, s1, t1 //divide passed num (s1) by previous guess (t1) 
    mflo s0 //moves quotient to s0
    addu s0, s0, t1 //adds quotient (s0) to previous guess (t1)
    srl s0, s0, 1 //(s0 / 2)
    subu s2, t1, s0 // s2 = previous guess (t1) - guess (s0)
    addiu s2, s2, -1 //subtract 1 from s2
    bgez s2, isqrt_loop
    addiu s2, s2, 1 //add 1 to s2 
isqrt_done:
    addu v0, $0, s0 //v0 = guess
    
    multu v0, v0
    mflo t0
    
    bleu t0, s1, isqrt_return
    nop
    addiu v0, v0, -1
isqrt_return:    
    lw ra, 20(sp)
    lw fp, 16(sp)
    lw s3, 12(sp)
    lw s2, 8(sp)
    lw s1, 4(sp)
    lw s0, 0(sp)
    addiu sp, sp, 24
    
    jr ra
    nop
    
.end isqrt
 
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