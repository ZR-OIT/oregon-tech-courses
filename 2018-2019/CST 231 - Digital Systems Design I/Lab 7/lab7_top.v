`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Tech
// Engineer: Zak Rowland
// 
// Create Date:    15:27:03 02/21/2019 
// Design Name: 	 Keypad controller
// Module Name:    lab7_top 
// Project Name: 		Lab7 - Keypad
// Target Devices: 	OwlBoard
// Tool versions: 
// Description: 	This is the top level module for Lab7 - Keypad.
//						Used to control all other modules.
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module lab7_top(

	input CLK,
	input [3:0] KEYPAD_COL, //column
	output [3:0] KEYPAD_ROW, //row
	output [7:0] SSEG,
	output [1:0] SSEGA,
	output DATA_OUT

);

wire clk_div_1KHz; //1KHz clock wire
wire clk_div_9600Hz; //9600Hz clock wire
wire go_tx;
wire [7:0] tx_char;
wire [4:0] scanner_output; //5-bit output from keypad scanner

assign SSEGA = 2'b01;

clkdiv_48MHz_to_1KHz 	clock_1KHz(.clk(CLK),.clk_div(clk_div_1KHz));
clkdiv_48MHz_to_9600Hz	clock_9600Hz(.clk_in(CLK),.clk_out(clk_div_9600Hz));
keypad_scanner 			scan_keypad(.clk(clk_div_1KHz),.column(KEYPAD_COL),.row(KEYPAD_ROW),.decoded(scanner_output));
lab7_decoder 			sseg_display(.bin_in(scanner_output),.sseg_out(SSEG));
tx_decoder				transmitter_decoder(.clk(clk_div_9600Hz),.data(scanner_output),.go(go_tx),.tx_character(tx_char));
tx_message				transmitter_message(.clk(clk_div_9600Hz),.datain(tx_char),.go(go_tx),.dataout(DATA_OUT));

endmodule
