`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date: 13:36:24 01/24/2019 
// Design Name: Seven segment display test   
// Module Name: top 
// Project Name: Lab 3
// Target Devices: OwlBoard
// Tool versions: 
// Description: This module tests the functionality of the dual digit 7-segment display.
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
assign LED[11:0] = 12'b000000000000;

wire clk_wire_500hz;
wire clk_wire_1hz;
wire [7:0] count_value;
wire [7:0] digit_one_val;
wire [7:0] digit_two_val;

clk_divider_to_500hz clock500hz(.clk(CLK),.reset(1'b0),.clk_div(clk_wire_500hz)); //500Hz clock divider module
clk_divider_to_1hz clock1hz(.clk(CLK),.reset(1'b0),.clk_div(clk_wire_1hz)); //1Hz clock divider module

counter99 county(.clk(clk_wire_1hz),.count_out_dig_one(count_value[3:0]),.count_out_dig_two(count_value[7:4])); //0-99 counter module

lab3_decoder decode_digit_one(.bin_in(count_value[3:0]),.sseg_out(digit_one_val)); //binary to sseg decoder modules
lab3_decoder decode_digit_two(.bin_in(count_value[7:4]),.sseg_out(digit_two_val));

sseg_driver sseg(.clk(clk_wire_500hz),.digit_one(digit_two_val),
					.digit_two(digit_one_val),.drive_sseg(SSEG[7:0]),.drive_anode(SSEGA[1:0])); //sseg display driver module

endmodule