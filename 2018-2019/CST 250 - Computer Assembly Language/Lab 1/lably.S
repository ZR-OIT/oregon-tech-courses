/* 
    Zak Rowland - 9/27/2018 - Lab1 lably
*/
#include <p32xxxx.h>
.global main
.set noreorder

.data
var_a: .word 0x7fffffff
var_b: .word 0x10000000
var_c: .space 4
var_d: .space 4
    
.text
main:
    la t0, var_c //loads address of var_c into t0
    li t1, 0x20000000 //loads value into t1
    sw t1, 0(t0) //stores value from t1 into t0 (var_c)
    
    la t0, var_a //loads address of var_a into t0
    lw t1, 0(t0) //loads value of var_a into t1
    la t0, var_b //loads address of var_b into t0
    lw t2, 0(t0) //loads value of var_b into t2
    addu t3, t1, t2 //adds t1 and t2 to store into t3
    la t0, var_c //loads address of var_c into t0
    lw t1, 0(t0) //loads value of var_c into t1
    subu t3, t3, t1 //subtracts value of t3 by var_c
    la t0, var_d //loads address of var_d into t0
    sw t3, 0(t0) //stores resulted value into var_d
    
    j .
    nop