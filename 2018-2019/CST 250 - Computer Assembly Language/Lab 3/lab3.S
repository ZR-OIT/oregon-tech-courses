/* Zak Rowland, 10/11/2018 
   Lab 3 - Basic Subroutines
   
   - C Pseudocode-
    
   char test_str[] = "0word1 1word2 3word4.";
   int dCount = 0;
   int dSum = 0;
     
   char * str_ptr = test_str;
   
   while(str_ptr != NULL)
   {
     if(is_a_digit(str_ptr) != -1)
     {
	dCount++;
	dSum += (str_ptr - 0x30);
     }
     else
     {
	str_ptr++;
     }
   }
     
*/
#include <p32xxxx.h>
.global main
.set noreorder

.data
    test_str1: .asciiz "/This 1 is 2 a 3 most 4 excellent 5 test 6 string 7 for 8 Lab 9 3. 0:"
    dCount: .word 0
    dSum: .word 0
.text
    .align 2  // need to make sure the data before the code does not
             // cause it to become un-aligned.
.ent main
main:
    addiu sp, sp, -16 //reserve stack space for 4 items
    sw ra, 12(sp) //save ra
    sw s0, 8(sp) //save s0 for caller
    sw s1, 4(sp) //save s1 for caller
    sw s2, 0(sp) //save s2 for caller
    
    la s0, test_str1 //loads address of string into register s0
    li s1, 0 //initialize dCount to 0 in register s1
    li s2, 0 //initialize dSum to 0 in register s2
    lbu a0, 0(s0) //loads a character into register a0
    beq a0, $0, done //if char is null skip to done
begin:
    jal is_a_digit //jumps to is_a_digit subroutine
    nop
    bltz v0, skip //if -1 is returned skip to next char
    nop
    addiu s1, s1, 1 //increase the count by 1
    addu s2, s2, v0 //increase the sum by the returned digit
skip:
    addiu s0, s0, 1 //points to next char
    lbu a0, 0(s0) //loads a character into register a0
    bne a0, $0, begin //if char isn't null loop to beginning
    nop
done:    
    sw s1, dCount //store count into dCount
    sw s2, dSum //store sum into dSum
    
    lw ra, 12(sp) //restore ra
    lw s0, 8(sp) //restore s0 for caller
    lw s1, 4(sp) //restore s1 for caller
    lw s2, 0(sp) //restore s2 for caller
    addiu sp, sp, 16 //release stack space
    
    j .
    nop
.end main
    
.ent is_a_digit    
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
    
    