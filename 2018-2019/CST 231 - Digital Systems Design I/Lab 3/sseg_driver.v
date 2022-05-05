`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date:    14:47:14 01/28/2019 
// Design Name:		Seven segment display test 
// Module Name:    sseg_driver 
// Project Name: 	Lab 3
// Target Devices:  OwlBoard
// Tool versions: 
// Description: This module receives all required inputs to multiplex and drive the display.
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module sseg_driver(
	input clk,
	input [7:0] digit_one,
	input [7:0] digit_two,
	output reg [7:0] drive_sseg,
	output reg [1:0] drive_anode
);

always @ (digit_one or digit_two) begin

	if(clk) begin
		drive_anode = 2'b01;
		drive_sseg = digit_one;
	end
	else begin
		drive_anode = 2'b10;
		drive_sseg = digit_two;
	end

end

endmodule
