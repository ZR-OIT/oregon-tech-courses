`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:				Oregon Institute of Technology
// Engineer: 			Zak Rowland
// 
// Create Date:    	12:40:04 03/02/2019 
// Design Name: 		Pulse Width Modulation RGB LED Control
// Module Name:    	variable_pwm
// Project Name: 		Lab8
// Target Devices: 	OwlBoard
// Tool versions: 
// Description:		Generates a variable duty cycle clock that is controlled by the counter module.
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module variable_pwm(

	input clk, //48MHz input clock
	input [3:0] count, //duty cycle deciding input
	output reg pwm_signal //pwm output

);

reg [3:0] pwm_counter = 4'd0;

always @ (posedge clk) begin
	
	if(count > pwm_counter) pwm_signal = 1'b1;
	else pwm_signal = 1'b0;
	
	pwm_counter = pwm_counter + 1'b1;
	
end 
endmodule