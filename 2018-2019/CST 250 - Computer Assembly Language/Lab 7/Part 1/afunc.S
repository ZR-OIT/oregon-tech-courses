/* Zak Rowland - 11/28/2018
   Lab 7 - Part 1 */
#include <p32xxxx.h>
.global isqrt
.global output_string
.global uart_init
.set noreorder
    
.data

.text
.ent uart_init
uart_init:
/*************************************************************************
Function: uart_init
Purpose: Configures UART for output
Arguments: None
*************************************************************************/
// configure Uart1 for TX
     li   t0, 0x8000
     sw   t0, U1MODESET // Turn UART1 ON
     li   t0, 0x1400
     sw   t0, U1STASET  // Enable Receive and Transmit
// done configuring UART1
.end uart_init
    
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
    
    srl s0, s0, 1 //(t0 / 2) = guess
    
isqrt_loop:
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