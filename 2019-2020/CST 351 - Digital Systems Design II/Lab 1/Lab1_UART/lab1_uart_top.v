`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Hayden Hutsell / Zak Rowland
// 
// Create Date:    15:24:12 02/07/2019 
// Design Name: 
// Module Name:    top_lab5 
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
module lab1_uart_top(
    input CLOCK_50,
	 input [0:0] KEY,
	 output DATA_OUT
    );
	 wire [7:0] tx_char;
	 reg [79:0] transmit_message  = 80'hafafafafafafafafafaf;
	 wire clk_div;
	 wire go_tx;
	 
clkdiv_50MHz_to_9600Hz clock_9600Hz(.clk_in(CLOCK_50), .clk_out(clk_div));
lab5_tx_message uart_tx(.clk(clk_div),.go(go_tx), .datain(tx_char), .dataout(DATA_OUT)); //outputs 8bit data sent from tx_char
lab5_tx_driver message_controller(.clk(clk_div), .switch(~KEY[0]), .message(transmit_message), .tx_character(tx_char), .go (go_tx)); //gets fed a message, outputs it one character at a time to tx module

endmodule