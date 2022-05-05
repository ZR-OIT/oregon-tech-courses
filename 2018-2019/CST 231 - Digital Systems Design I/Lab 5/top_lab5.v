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
module top_lab5(
    input CLK,
	 input [1:0] SW,
	 output DATA_OUT,
	 output LED
    );
	 wire [7:0] tx_char;
	 reg [79:0] transmit_message  = 80'h6e6f6974616e65706176; //"vapenation" reversed
	 wire clk_div;
	 wire go_tx;
	 
	 

	 
clkdiv_48mhz_9600or38400hz var_clk_div(.clk_in(CLK), .clk_out(DATA_OUT), .button(~SW[0]), .led(LED)); //variable clock divider depending on if button is pressed
tx_message uart_tx(.clk(clk_div),.go(go_tx), .datain(tx_char), .dataout(DATA_OUT)); //outputs 8bit data sent from tx_char
tx_driver message_controller(.clk(clk_div), .switch(~SW[1]), .message(transmit_message), .tx_character(tx_char), .go (go_tx)); //gets fed a message, outputs it one character at a time to tx module
endmodule