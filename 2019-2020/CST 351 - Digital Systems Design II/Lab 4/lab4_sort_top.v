`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date: 15:21:00 05/05/2020 
// Design Name: 
// Module Name: lab4_sort_top
// Project Name: Lab4
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
module lab4_sort_top(
	input CLOCK_50
);

	//parameter N = 19; // Number of 2-input 2-output sort modules, 19 for 8 in/8 out
	
	reg [7:0] data_to_sort [7:0]; // 8-element arrays of 8-bits
	wire [7:0] sorted [7:0];
	
	/*
	genvar i; // Temporary loop variable for generation
	
	generate // Generate for loop to instantiate N modules
		
		for (i = 0; i < N; i = i + 1) begin : generated_sort
		
			sort_2x8bit u0 (a[i], b[i], c[i], d[i]);
		
		end
		
	endgenerate
	*/
	
	initial begin
	
		data_to_sort[0] = 8'd80;
		data_to_sort[1] = 8'd40;
		data_to_sort[2] = 8'd120;
		data_to_sort[3] = 8'd0;
		data_to_sort[4] = 8'd60;
		data_to_sort[5] = 8'd255;
		data_to_sort[6] = 8'd180;
		data_to_sort[7] = 8'd20;
	
	end
	
	/*
	sort_2x8bit sort1(.a(data_to_sort[0]), .b(data_to_sort[1]), .c(sorted[0]), .d(sorted[1]));
	sort_2x8bit sort2(.a(data_to_sort[2]), .b(data_to_sort[3]), .c(sorted[2]), .d(sorted[3]));
	sort_2x8bit sort3(.a(data_to_sort[4]), .b(data_to_sort[5]), .c(sorted[4]), .d(sorted[5]));
	sort_2x8bit sort4(.a(data_to_sort[6]), .b(data_to_sort[7]), .c(sorted[6]), .d(sorted[7]));
	sort_2x8bit sort5(.a(sorted[0]), .b(sorted[2]), .c(sorted[0]), .d(sorted[2]));
	sort_2x8bit sort6(.a(sorted[4]), .b(sorted[6]), .c(sorted[4]), .d(sorted[6]));
	sort_2x8bit sort7(.a(sorted[1]), .b(sorted[3]), .c(sorted[1]), .d(sorted[3]));
	sort_2x8bit sort8(.a(sorted[5]), .b(sorted[7]), .c(sorted[5]), .d(sorted[7]));
	sort_2x8bit sort9(.a(sorted[1]), .b(sorted[2]), .c(sorted[1]), .d(sorted[2]));
	sort_2x8bit sort10(.a(sorted[5]), .b(sorted[6]), .c(sorted[5]), .d(sorted[6]));
	sort_2x8bit sort11(.a(sorted[0]), .b(sorted[4]), .c(sorted[0]), .d(sorted[4]));
	sort_2x8bit sort12(.a(sorted[1]), .b(sorted[5]), .c(sorted[1]), .d(sorted[5]));
	sort_2x8bit sort13(.a(sorted[2]), .b(sorted[6]), .c(sorted[2]), .d(sorted[6]));
	sort_2x8bit sort14(.a(sorted[3]), .b(sorted[7]), .c(sorted[3]), .d(sorted[7]));
	sort_2x8bit sort15(.a(sorted[2]), .b(sorted[4]), .c(sorted[2]), .d(sorted[4]));
	sort_2x8bit sort16(.a(sorted[3]), .b(sorted[5]), .c(sorted[3]), .d(sorted[5]));
	sort_2x8bit sort17(.a(sorted[1]), .b(sorted[2]), .c(sorted[1]), .d(sorted[2]));
	sort_2x8bit sort18(.a(sorted[3]), .b(sorted[4]), .c(sorted[3]), .d(sorted[4]));
	sort_2x8bit sort19(.a(sorted[5]), .b(sorted[6]), .c(sorted[5]), .d(sorted[6]));
	
	always @ (*) begin
	
		
	
	end
	*/
endmodule