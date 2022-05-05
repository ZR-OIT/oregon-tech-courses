`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date: 11:43:00 05/12/2020 
// Design Name: 
// Module Name: lab5_top
// Project Name: Lab5
// Target Devices: Cyclone V - DE1-SoC
// Tool versions: Quartus Lite 19.1
// Description: 
//
// Dependencies:
//
// Revisions: 
// - Revision 0.01: File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module lab5_top(

	input CLOCK_50,
	input [9:0] SW,
	output [9:0] LEDR

);

	wire [31:0] count_top;

	assign LEDR[9:1] = SW[9:1];
	
	counter_32bit counter(.clk(CLOCK_50), .reset(SW[0]), .count(count_top), .go(LEDR[0]));

endmodule
