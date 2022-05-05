`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Hayden Hutsell and Zak Rowland
// 
// Create Date:    15:22:19 02/14/2019 
// Design Name: 
// Module Name:    lab6_top 
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
module lab6_top(
	input CLK, 
	input SW, 
	input DATA_IN,
	output [1:0] LED, //one is on for variable clk, other is on for parity
	output [7:0] SSEG,
	output [1:0]SSEGA  //sseg anode
	);

wire clk_div_uart; //wire for uart
wire clk_div_sseg; //wire for multiplexing sseg
wire [7:0] data_received; //wire to send the serial data to the sseg
wire data_rdy; //data ready flag for sseg
wire [15:0] digit_out; //digits to send to sseg


clkdiv_receiver8x_76800or307200hz receiver_clk(.clk_in(CLK),.button(~SW),.led(LED[0]),.clk_out(clk_div)); //variable clk divider
rx receiver(.clk(clk_div), .data_in(DATA_IN), .parity_led(LED[1]), .data_out(data_received), .data_ready(data_rdy)); //receiver state machine module
clk_divider_48mhz_to_500hz sseg_clk(.CLK(CLK), .divided_CLK(clk_div_sseg)); //clk divider for sseg multiplexing
SSEG_sel sseg_selector(.clk_500hz(clk_div_sseg), .SSEGA(SSEGA));//multiplexes anodes
SSEG_output ascii_output(.clk(clk_div_sseg), .digits(digit_out), .SSEG_digit(SSEG)); //multiplexes cathodes
bcd_decoder digit_decoder1(.D(data_received[3:0]), .sseg_out(digit_out[7:0]), .data_rdy(data_rdy), .clk(CLK)); //decoder for digit 1
bcd_decoder digit_decoder2(.D(data_received[7:4]), .sseg_out(digit_out[15:8]), .data_rdy(data_rdy), .clk(CLK)); //decoder for digit 2

endmodule
