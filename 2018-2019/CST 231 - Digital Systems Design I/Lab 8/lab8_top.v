`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:				Oregon Institute of Technology
// Engineer: 			Zak Rowland
// 
// Create Date:    	12:31:54 03/02/2019 
// Design Name: 		Pulse Width Modulation RGB LED Control
// Module Name:    	lab8_top 
// Project Name: 		Lab8
// Target Devices: 	OwlBoard
// Tool versions: 
// Description: 		This module simply instantiates and connects modules and pins.
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module lab8_top(

	input CLK,
	output RGB_R,
	output RGB_G,
	output RGB_B,
	output RGB_CATHODE //LEDs are common cathode
	
);

	assign RGB_CATHODE = 1'b0;

	wire [3:0] duty_count; //count for duty cycle
	wire clock_wire_10KHz; //generated 10KHz signal
	wire clock_wire_10Hz; //generated 10Hz signal
	wire pwm_wire; //generated pwm signal

	clk_divider_to_10KHz 			clock_10KHz(.clk(CLK),.clk_div(clock_wire_10KHz));
	clk_divider_to_10Hz				clock_10Hz(.clk(CLK),.clk_div(clock_wire_10Hz));
	counter 								duty_counter(.clk(clock_wire_10Hz),.pwm_signal(pwm_wire),.count_out(duty_count),.red(RGB_R),.green(RGB_G),.blue(RGB_B));
	variable_pwm 						generate_pwm(.clk(clock_wire_10KHz),.count(duty_count),.pwm_signal(pwm_wire));

endmodule
