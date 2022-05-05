`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:				Oregon Institute of Technology
// Engineer:			Zak Rowland
// 
// Create Date:		14:05:34 01/28/2019 
// Design Name: 		Pulse Width Modulation RGB LED Control 
// Module Name:    	clk_divider_to_10KHz 
// Project Name: 		Lab8
// Target Devices: 	OwlBoard
// Tool versions: 
// Description: 		This module receives a 48MHz clock signal and divides it
//							to a 10KHz signal at 50% duty cycle.
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module clk_divider_to_10KHz(
	input clk,
	output reg clk_div
);
// 48MHz / 10KHz = 4,800
parameter constantNum = 12'd2400; //Count to 2,400 for 10KHz at 50% duty cycle

reg [11:0] count; //12 bit counter

always @ (posedge clk) begin
	if(count == constantNum) begin //if counter equals constant, invert clock and reset counter
		count <= 12'd0;
		clk_div <= ~clk_div;
	end
	else count <= count + 1'd1; //else add 1

end
endmodule
