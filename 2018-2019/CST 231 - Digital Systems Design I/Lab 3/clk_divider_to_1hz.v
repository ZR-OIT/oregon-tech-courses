`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date:    14:05:34 01/28/2019 
// Design Name: 	Seven segment display test 
// Module Name:    clk_divider_to_1hz 
// Project Name: 	Lab 3
// Target Devices: 	Owlboard
// Tool versions: 
// Description: 	This module receives a 48MHz clock signal and divides it to a 1Hz signal at 50% duty cycle.
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module clk_divider_to_1hz(
	input clk,
	input reset,
	output reg clk_div
);

parameter constantNum = 25'd24000000; //Count to 24,000,000 for 1Hz at 50% duty cycle

reg [24:0] count; //25 bit counter

always @ (posedge clk or posedge reset) begin

	if(reset == 1'b1) begin
		count <= 25'd0;
		clk_div <= 1'b0;
	end
	else if(count == constantNum) begin //if counter equals constant, invert clock and reset counter
		count <= 25'd0;
		clk_div <= ~clk_div;
	end
	else count <= count + 1'd1; //else add 1

end
endmodule
