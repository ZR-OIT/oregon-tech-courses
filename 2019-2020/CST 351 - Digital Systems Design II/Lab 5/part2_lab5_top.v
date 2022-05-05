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
// https://docs.google.com/spreadsheets/d/1m7a4VIcCA8lYOjrzw0Y5c0ykSuc0MIbC0YkP8jdpj10/edit?pli=1#gid=0
//
//////////////////////////////////////////////////////////////////////////////////
module lab5_top(

	input CLOCK_50,
	input [9:0] SW,
	output [9:0] LEDR

);

	wire [7:0] counter1_out;
	wire [7:0] counter2_out;
	wire [7:0] counter3_out;
	wire [7:0] counter4_out;

	wire counter1_go;
	wire counter2_go;
	wire counter3_go;
	wire counter4_go;
	
	wire counter1_start;
	wire counter2_start;
	wire counter3_start;
	wire counter4_start;
	
	assign LEDR[9:1] = SW[9:1];
	assign LEDR[0] = counter4_go;
	
	assign counter1_start = (counter1_out == 8'd0 && counter2_out == 8'd0 && counter3_out == 8'd0 && counter4_out == 8'd0 && counter1_go == 1'b0 && counter2_go == 1'b0 && counter3_go == 1'b0 && counter4_go == 1'b0) ? 1'b1 : 1'b0;
	assign counter2_start = counter1_go;
	assign counter3_start = counter2_go;
	assign counter4_start = counter3_go;
	
	counter_8bit counter1(.clk(CLOCK_50), .reset(SW[0]), .start(counter1_start), .count(counter1_out), .go(counter1_go));
	counter_8bit counter2(.clk(CLOCK_50), .reset(SW[0]), .start(counter2_start), .count(counter2_out), .go(counter2_go));
	counter_8bit counter3(.clk(CLOCK_50), .reset(SW[0]), .start(counter3_start), .count(counter3_out), .go(counter3_go));
	counter_8bit counter4(.clk(CLOCK_50), .reset(SW[0]), .start(counter4_start), .count(counter4_out), .go(counter4_go));
	
endmodule
