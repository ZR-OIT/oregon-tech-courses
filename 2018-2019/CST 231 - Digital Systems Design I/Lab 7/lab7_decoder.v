`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Tech
// Engineer: Zak Rowland
// 
// Create Date:    15:34:23 02/21/2019  
// Design Name: 	 SSEG Display decoder
// Module Name:    lab7_decoder
// Project Name: 		Lab7 - Keypad
// Target Devices: 	OwlBoard
// Tool versions: 
// Description: 	This module receives a 5-bit binary value and decodes it to an 
//						8-bit binary value to be displayed on the seven segment.
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

module lab7_decoder(
input [4:0] bin_in, //5 bit binary input
output reg [7:0] sseg_out
);

always @ (bin_in) begin

	case(bin_in)
		
		5'b10001: sseg_out = 8'b11000000; //0
		5'b00001: sseg_out = 8'b11111001; //1
		5'b00010: sseg_out = 8'b10100100; //2
		5'b00011: sseg_out = 8'b10110000; //3
		5'b00100: sseg_out = 8'b10011001; //4
		5'b00101: sseg_out = 8'b10010010; //5
		5'b00110: sseg_out = 8'b10000010; //6
		5'b00111: sseg_out = 8'b11111000; //7
		5'b01000: sseg_out = 8'b10000000; //8
		5'b01001: sseg_out = 8'b10010000; //9
		5'b01010: sseg_out = 8'b10001000; //10 - A
		5'b01011: sseg_out = 8'b10000011; //11 - B
		5'b01100: sseg_out = 8'b11000110; //12 - C
		5'b01101: sseg_out = 8'b10100001; //13 - D
		5'b10000: sseg_out = 8'b11111110; //*
		5'b10010: sseg_out = 8'b11110111; //#
		5'b11111: sseg_out = 8'b01111111; //blank
		default: sseg_out = 8'b01111111;
		
	endcase
	
end
endmodule