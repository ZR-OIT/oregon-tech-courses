/* Zak Rowland - 11/8/2018
   Lab 8 - Hex Memory Dump */
    
#include <p32xxxx.h>
.global main
.set noreorder
    
.data
address_lower: .asciiz "yA9d,00x0301x"
address_upper: .asciiz "9D000220"

space_str: .asciiz "  "
test_str: .asciiz "abcdef123456789" //address = 0xA0000215
CrLf:     .asciiz "\n\r"

table_sections: .asciiz "Address    F  E  D  C   B  A  9  8   7  6  5  4   3  2  1  0"
table_divider:  .asciiz "========  ===========  ===========  ===========  ==========="
    
hex_str: .space 13 //space for up to 12 ascii hex characters and a null
.text
    
.ent main
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
Function: main
Purpose: Controls the process of displaying memory hex dump
Arguments: None
*************************************************************************/
//s0 holds lower address
//s1 holds upper address
//s2 holds current address

main:
    addiu sp, sp, -20
    sw ra, 16(sp)
    sw fp, 12(sp)
    sw s2, 8(sp)
    sw s1, 4(sp)
    sw s0, 0(sp)
    
    // configure Uart1 for TX
     li   t0, 0x8000
     sw   t0, U2MODESET // Turn UART1 ON
     li   t0, 0x1400
     sw   t0, U2STASET  // Enable Receive and Transmit
    // done configuring UART1
    
    la a0, table_sections
    jal output_string //display table labels
    nop
    
    la a0, CrLf
    jal output_string //display new line
    nop
    
    la a0, table_divider
    jal output_string //display table divider
    nop
    
    la a0, CrLf
    jal output_string //display new line
    nop
    
    la a0, address_lower
    jal asciihex_to_binary //convert lower address to binary
    nop
    
    li t0, 0xFFFFFFF0 
    and s0, t0, v0 //set lower byte of lower address to 0
    
    la a0, address_upper
    jal asciihex_to_binary //convert upper address to binary
    nop
    
    li t0, 0xFFFFFFF0
    and s1, t0, v0 //set lower byte of upper address to 0
main_display_address:
    addu a0, $0, s0 //pass lower address to a0
    li a1, 0 //flag is 0
    la a2, hex_str
    jal binary_to_asciihex //convert lower address to hex
    nop
    
    la a0, hex_str
    jal output_string //display address
    nop
    addiu s2, s0, 0xC //add C to lower address
main_display_data:
    la a0, space_str
    jal output_string //display double space
    nop
    
    lw a0, 0(s2)
    li a1, 1 //flag is 1, add space
    la a2, hex_str
    jal binary_to_asciihex //convert current address data to hex
    nop
    
    la a0, hex_str
    jal output_string //display hex data
    nop
    
    addiu s2, s2, -4 //subract 4 from current address
    bge s2, s0, main_display_data //if current address >= lower address, loop
    nop
main_switch_rows:
    la a0, CrLf
    jal output_string //display new line
    nop
    
    addiu s0, s0, 0x10 //move lower address to next row
    
    ble s0, s1, main_display_address //if lower address <= upper address, loop
    nop
    
    lw ra, 16(sp)
    lw fp, 12(sp)
    lw s2, 8(sp)
    lw s1, 4(sp)
    lw s0, 0(sp)
    addiu sp, sp, 20
    
    j .
    nop
.end main
    
.ent asciihex_to_binary
/*********************
    Stack Frame
 ====Reg Save Area====
 ra		28		
 fp		24
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
Function: asciihex_to_binary
Purpose: Converts an ascii hex string into a binary representation.
Arguments: An address of a string in a0, the converted value is returned in v0.
*************************************************************************/
asciihex_to_binary:
    addiu sp, sp, -16
    sw ra, 12(sp)
    sw fp, 8(sp)
    sw s1, 4(sp)
    sw s0, 0(sp)
    
    //s0 holds total value
    //s1 holds address of string
    
    li s0, 0 //initialize total value (s0) to 0
    addu s1, $0, a0 //copies address of passed string into s1
    
    lbu a0, 0(s1) //loads a character from string into register a0
    beq a0, $0, hex_to_bin_done //if char is null skip to done
    nop
hex_to_bin_convert:
    jal is_a_hex_digit //jumps to is_a_hex_digit subroutine
    nop
    bltz v0, hex_to_bin_skip //if -1 is returned skip to next char
    nop
    
    sll s0, s0, 4 //shift total value left 4 bits (multiply by 16)
    addu s0, s0, v0 //adds result of is_a_hex_digit to total value
hex_to_bin_skip:
    addiu s1, s1, 1 //points to next char in string
    lbu a0, 0(s1) //loads a char from string into a0
    bne a0, $0, hex_to_bin_convert //if char isn't null, loop
    nop
hex_to_bin_done:
    addu v0, s0, $0 //copies total value from s0 into v0
    
    lw ra, 12(sp)
    lw fp, 8(sp)
    lw s1, 4(sp)
    lw s0, 0(sp)
    addiu sp, sp, 16
    
    jr ra
    nop
.end asciihex_to_binary
    
.ent is_a_hex_digit
/*************************************************************************
Function: is_a_hex_digit
Purpose: Tests if a character from a string is an acceptable hex digit.
Arguments: a0 holds a byte (character) and v0 returns a -1 if not a valid hex
	    digit, or the value of the digit if it is valid.
*************************************************************************/
is_a_hex_digit:
    
    li v0, -1 //loads -1 into v0
    li t0, 0x30 //loads 0x30 into register t0
    blt a0, t0, hex_digit_done //char is not valid hex if less than 0x30
    //nop
    li t0, 0x39 //loads 0x39 into register t0
    ble a0,t0, num_hex //char is in 0-9 range
    //nop
    li t0, 0x40 //loads 0x40 into register t0
    ble a0, t0, hex_digit_done //char is not valid hex if less than 0x40
    //nop
    andi a0, a0, 0xDF //ANDs char with 0xDF
    li t0, 0x46 //loads 0x46 into register t0
    ble a0, t0, alpha_hex //char is in A-F range
    nop
    bgt a0, t0, hex_digit_done //char is not valid hex if greater than 0x46
    nop
num_hex:
    li t0, 0x30 //loads 0x30 into register t0
    subu v0, a0, t0 //subtracts 0x30 from char, stores into v0
    j hex_digit_done
    nop
alpha_hex:
    li t0, 0x37 //loads 0x37 into register t0
    subu v0, a0, t0 //subtracts 0x37 from char, stores into v0
hex_digit_done:
    jr ra
    nop
    
.end is_a_hex_digit
    
.ent binary_to_asciihex
/*************************************************************************
Function: binary_to_asciihex
Purpose: Converts a binary number into an ascii hex string
	    representation of that number.
Arguments: An integer value in register a0, an integer flag in register a1,
	    and a pointer to an 17 byte space in the .data segment in register a2.
*************************************************************************/
binary_to_asciihex:
    
    //t0 is count
    //t1 is rotated and ANDed value
    //t2 is for temp values
    //space = 0x20
    
    addu t0, $0, $0 //initialize count (t0) to 0
    la t3, hex_str //load a pointer to empty string into t3
bin_to_hex_convert:
    rotr a0, a0, 28 //rotate passed value right 28 bits and store in a0
    andi t1, a0, 0x0F //AND rotated value with 0x0F
    li t2, 9 //loads 9 into register t2
    ble t1, t2, num_bin //if t1 is less than or equal to 9, the value is a number
    nop
alpha_bin:
    addiu t1, t1, 0x37 //adds 0x37 to binary value to convert to hex
    j fill_string
    nop
num_bin:
    addiu t1, t1, 0x30 //adds 0x30 to binary value to convert to hex
fill_string:
    sb t1, 0(a2) //store converted character into empty string
    addiu a2, a2, 1 //move pointer to next empty space
    addiu t0, t0, 1 //increment counter
    
    li t2, 8 //load 8 into t2
    beq t0, t2, bin_to_hex_done //if counter does equals 8, done
    nop
fill_space:
    li t2, 1 //load 1 into t2
    bne a1, t2, bin_to_hex_convert //if a1 does not equal 1, space is not added
    nop
    andi t2, t0, 0x01 //AND counter with 0x01
    bne t2, $0, bin_to_hex_convert //if AND result is not 0, dont add space
    nop
    li t2, 0x20 //load 0x20 (space) into register t2
    sb t2, 0(a2) //store converted character into empty string
    addiu a2, a2, 1 //move pointer to next empty space
    j bin_to_hex_convert
bin_to_hex_done:
    li t2, 0x0 //load a null character into t2
    sb t2, 0(a2)
    jr ra
    nop
.end binary_to_asciihex
    
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
     sw    t0, U2TXREG    // send data to Uart1

wait_tx:
     lw    t0, U2STA          // get Uart1 Status  
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