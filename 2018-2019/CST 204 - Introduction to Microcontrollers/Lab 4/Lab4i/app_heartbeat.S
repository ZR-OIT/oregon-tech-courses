//Author: Hayden Hutsell and Zak Rowland
//Date: 1/17/2019
//app_heatbeat.S
//This program is implemented as a 2 state FSM
    
#include <xc.h>
.global app_heartbeat
.text
.set noreorder
    
.ent app_heartbeat
    app_heartbeat:
	lw a0, heartbeat_count
	addiu a0, a0, 1 
	sw a0, heartbeat_count //increment heartbeat count
	
	lw a1, heartbeat_state //put the state in a1
	
	beq a1, $0, state_0 //jump to state 0
	nop
	
	addiu a2, $0, 99 //if we get to 99, need to turn off led
	beq a0, a2, turn_off 
	nop
	j exit //not been .25, do nothing
	nop
	
	state_0:
    
	addiu a2, $0, 74 //if we get to 74, we need to turn on led
	beq a2, a0, turn_on
	nop
	j exit //not been .75, do nothing
	nop
	
	turn_on:
	la v0, PORTASET
	li v1, 0x80 //turn on LED connected to RA7
	sw v1, 0(v0)
	addiu a0, $0, 1
	sw a0, heartbeat_state //set state to state 1
	j exit
	nop
	
	turn_off:
	la v0, PORTACLR
	li v1, 0x80 //turn off LED connected to RA7
	sw v1, 0(v0)
	addiu a0, $0, 0
	sw a0, heartbeat_state //set state to state 0
	sw a0, heartbeat_count //reset heartbeat count to 0
	
	exit:
    
	jr ra //return to caller
	nop
.end app_heartbeat