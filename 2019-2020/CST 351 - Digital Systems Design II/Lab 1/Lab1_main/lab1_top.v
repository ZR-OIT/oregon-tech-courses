`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:				Oregon Institute of Technology
// Engineer: 			Zak Rowland
// 
// Create Date:    	4/7/2020 
// Design Name: 		SignalTap
// Module Name:    	lab1_top
// Project Name: 		Lab1
// Target Devices: 	DE1-SoC (Cyclone V)
// Tool versions: 
// Description: 		This module ...
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

module lab1_top(

	input CLOCK_50,
	input [3:0] KEY,
	output reg [3:0] LEDR

);

	wire ab,

	always @ (posedge CLOCK_50)
		LEDR[3:0] <= KEY[3:0];

endmodule