/* 
   file: main.S
   author: Zak Rowland, Hayden Hutsell
   date: 1/10/2019
   description: Turns LED off/on depending if push button is pressed or not
*/
    
#include <xc.h>
 
.global main
.text
.set noreorder
 
.ent main
 
main:
   io_setup:
   la v0, TRISDSET
   li v1, 0b01000000 //set bit RD6 of PORTD as input
   sw v1, 0(v0)
    
   la v1, PORTACLR
   li v0, 0b10000000
   sw v0, 0(v1) //clear RA7 of PORTA
   la v1, ODCACLR
   li v0, 0b10000000
   sw v0, 0(v1) //set RA7 as closed drain output by clearing bit 7 ODCA
   la v0, TRISACLR
   li v1, 0b10000000
   sw v1, 0(v0) //set bit RA7 of PORTA as an output
   
   pb_loop: //push button pressed? loop
   la v0, PORTD
   lw v1, 0(v0)
   andi v1, v1, 0x40
   bne v1, zero, pb_not_pressed
   nop
   
   pb_pressed: //push button is pressed
   la v0, PORTASET
   li v1, 0x80 //turn on LED connected to RA7
   sw v1, 0(v0)
   j pb_loop //return to loop
   nop
   
   pb_not_pressed: //push button is not pressed
   la v0, PORTACLR
   li v1, 0x80 //turn off LED connected to RA7
   sw v1, 0(v0)
   j pb_loop //return to loop
   nop
.end main