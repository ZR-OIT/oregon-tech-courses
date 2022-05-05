`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
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
	 reg [7:0] ascii_F = 8'b01100001;
	 wire clk_div;
	 
clkdiv_48mhz_9600or38400hz var_clk_div(.clk_in(CLK), .clk_out(clk_div), .button(SW[0]), .led(LED));
tx output_A (.clk(clk_div),.go(~SW[1]), .data(ascii_F), .dataout(DATA_OUT));
endmodule
