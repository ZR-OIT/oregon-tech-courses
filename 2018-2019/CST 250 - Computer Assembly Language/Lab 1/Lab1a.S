/* 
    Zak Rowland - 9/27/2018 - Lab1 a
*/
#include <p32xxxx.h>
.global main
.set noreorder

.data
var_a: .word 0x7fffffff
var_b: .space 4
var_c: .space 4

.text
main:
    la t1, var_b //load address of var_b
    li t0, 0x10000000 //load constant into register t0
    sw t0, 0(t1) //store value from t0 register into t1 address (var_b)
    
    la t1, var_a //loads address of var_a
    lw t2, 0(t1) //loads value of var_a into t2
    addu t3, t2, t0 //adding var_a to var_b
    la t1, var_c //load address of var_c
    sw t3, 0(t1) //store value of t3 into var_c
    
    j .
    nop