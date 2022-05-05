`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:16:24 01/17/2019 
// Design Name: 
// Module Name:    top 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module top(
	input CLK,
	input [7:0] SW,
	output [11:0] LED,
	output [7:0] SSEG,
	output [1:0] SSEGA
);

assign LED[11:8] = 4'b1111;
assign LED[7:0] = SW[7:0];

assign SSEG[7:0] = 8'b00000000;
assign SSEGA[1:0] = 2'b11;


endmodule
