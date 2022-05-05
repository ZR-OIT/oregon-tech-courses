/* Zak Rowland
   10/4/2018
   Lab 2 - Basic Control using Structured Assembly
   
   C pseudo code:
     long int max_acc = 0;
     int x[] = { ... };
     int y[] = { ... };
     int n = number of elements in arrays;
     
     for(int i=0; i < n; i++)
     {
	if(x[i] < 0)
	{
	    x[i] = 0 - x[i];
	}
	if(x[i] != 0 && y[i] != 0)
	{
	    for(int j=0; j < x; j++)
	    {
		max_acc += y;
	    }
	}	
     }
*/
    
#include <p32xxxx.h>
.global main
.set noreorder

.data
MAC_ACC: .word 0

.text
X: .word 5, 0, -3, -10, 7
Y: .word 6, 0, -8, 1 ,-2
N: .word  5  // a count of the number of elements in the X and Y arrays
   .align 2  // need to make sure the data before the code does not
             // cause it to become un-aligned.
main:
    la t0, X	    // load X base address into t0
    la t1, Y	    // load y base address into t1
    li t2, 0	    // initialize MAC_ACC to 0
    li t3, 0	    // initialize count to 0
    lw t6, N	    // load number of elements
    beq t6, $0, done	// if there are no elements, skip to end

toploop:
    lw t4, 0(t0)    // load first element of X
    lw t5, 0(t1)    // load first element of Y

multiply:  
    beq t4, $0, skip	// if X = 0, branch to skip
    nop
    bgtz t4, notnegative	// if X is negative, branch to negative section
    nop
    negative:
    subu t4, $0, t4	// negates X
    subu t5, $0, t5	// negates Y
    notnegative:
    beq t5, $0, skip	// if Y = 0, branch to skip
    nop
    addu t2, t2, t5	// add Y to sum
    addiu t4, t4, -1	// decrement X
    bne t4, $0, multiply    // continue if X != 0
    nop

skip:
    addiu t3, t3, 1	// count + 1
    addiu t0, t0, 4	// point t0 at next element of X array
    addiu t1, t1, 4	// point t1 at next element of Y array
    bne t3, t6, toploop    // if count is less than number of elements, loop
    nop

done:
    sw t2, MAC_ACC  // stores sum into MAC_ACC
    j .
    nop
    
/*
    1. Items declared in the .text segment are read only and cannot be edited,
       and items declared in the .data segment are read/write and can be edited
       (variable.)
     
    2. The .space directive should not be used in the .text segment because
       .space is a placeholder of memory to be used later. If used in the .text
       segment, the memory isn't editable which means it is just wasted space.
*/