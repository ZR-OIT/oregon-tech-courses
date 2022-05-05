`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date: 15:22:00 05/05/2020 
// Design Name: 
// Module Name: sort_2bit
// Project Name: Lab4
// Target Devices: Cyclone V - DE1-SoC
// Tool versions: Quartus Lite 19.1
// Description: Sorts two 8-bit inputs.
//
// Dependencies:
//
// Revisions: 
// - Revision 0.01: File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module sort_2x8bit(

	input [7:0] a, // 8-bit input
	input [7:0] b, // 8-bit input
	output [7:0] c, // 8-bit output
	output [7:0] d // 8-bit output

);

	assign c = a > b ? a : b; // If first input is greater than second, swap outputs
	assign d = a > b ? b : a;

endmodule
