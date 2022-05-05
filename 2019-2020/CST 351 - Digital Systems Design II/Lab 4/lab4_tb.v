`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date: 11:23:00 05/12/2020 
// Design Name: 
// Module Name: lab4_tb
// Project Name: Lab4
// Target Devices: Cyclone V - DE1-SoC
// Tool versions: Quartus Lite 19.1
// Description: Testbench for the 8 input 8 output sorter
//
// Dependencies:
//
// Revisions: 
// - Revision 0.01: File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

module lab4_tb;

	parameter N = 4; // Number of 2-input 2-output sort modules
	reg [N-1:0] a [7:0];
	reg [N-1:0] b [7:0];
	wire [N-1:0] c [7:0];
	wire [N-1:0] d [7:0];
	
	lab4_sort_top #(tb_sort(.a(a), .b(b), .c(c), .d(d)));
	
	initial begin
	
		a[0] = 13;
		a[1] = 86;
		a[2] = 35;
		a[3] = 56;
		b[0] = 0;
		b[1] = 1;
		b[2] = 255;
		b[3] = 77;
	
	end
	
endmodule