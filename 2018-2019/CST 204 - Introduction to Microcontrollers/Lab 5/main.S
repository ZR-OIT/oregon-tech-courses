    
	#include <xc.h>
	.global main
	.text
	.set noreorder
	.ent main
		// Stack Frame
//===Reg Save area===
// ra      28
// old fp  24
// s1      20
// s0      16
//==Parameter space==
// res a3  12
// res a2  8
// res a1  4
// res a0  0
main: // {{{

	// TODO: Create stack frame

    
    addiu sp, sp, -24 //take space from stack pointer
    sw ra, 20(sp)//store old ra
    sw fp, 16(sp)//store old fp
    sw a0, 12(sp) //store old a0
    sw a1, 8(sp)  //store old a1
    sw a2, 4(sp) //store old a2
    sw a3, 0(sp) //store old a3
    addu fp, sp, $0 //set fp
    
jal		waitstates_config   //in hardware.S
nop

jal		gpio_config	//in hardware.S	
nop
    
jal		intsys_config
nop
    
jal		timer1_config
nop

jal		timer32_config
nop

jal lcd_config
nop
    
jal		lcd_time_init
nop
	while_1:
	wait_for_flag_10ms: //increments until 10 ms is reached
la		t1,		FLAG_10MS
lw		t0,		0(t1)
beq		t0,		zero,	wait_for_flag_10ms 
nop

	found_flat_10ms:
la		t1,		FLAG_10MS //sets a flag
sw		zero,		0(t1)

	perform_tasks:
jal		app_heartbeat //goes to our app
nop

jal app_clock
nop
jal svc_keypad
nop
jal app_test_keypad
nop
jal app_test_timer32
nop
    
j		while_1			// Continue loop
nop

    addu sp, fp, $0 //restore sp from fp
    lw ra, 20(sp)//restore ra
    lw fp, 16(sp)//restore fp
    lw a0, 12(sp) //restore a0
    lw a1, 8(sp) //restore a1
    lw a2, 4(sp) //restore a2
    lw a3, 0(sp) //restore a3
    addiu sp, sp, 24 //return space to the stack 
	// TODO: Remove stack frame

.end main
// }}}