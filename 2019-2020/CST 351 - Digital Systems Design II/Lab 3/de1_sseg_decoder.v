`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date: 19:02:00 05/01/2020 
// Design Name: 
// Module Name: de1_sseg_decoder
// Project Name: Lab3_nios2
// Target Devices: Cyclone V - DE1-SoC
// Tool versions: Quartus Lite 18.1
// Description: Drives a sseg display (HEX) attached to the DE1-SoC. LEDs are active low.
//
// Dependencies:
//
// Revisions: 
// - Revision 0.01: File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

module de1_sseg_decoder(

	input [6:0] data_in, // 7-bits of data in
	output reg [6:0] data_out // 7-bits of decoded data out to sseg

);

	always @ (data_in) begin
	
		case (data_in)
		
			7'b0000000: data_out = 7'b1000000; // 0
			7'b0000001: data_out = 7'b1111001; // 1
			7'b0000010: data_out = 7'b0100100; // 2
			7'b0000011: data_out = 7'b0110000; // 3
			7'b0000100: data_out = 7'b0011001; // 4
			7'b0000101: data_out = 7'b0010010; // 5
			7'b0000110: data_out = 7'b0000010; // 6
			7'b0000111: data_out = 7'b1011000; // 7
			7'b0001000: data_out = 7'b0000000; // 8
			7'b0001001: data_out = 7'b0010000; // 9
			7'b0001010: data_out = 7'b0001000; // 10 - a
			7'b0001011: data_out = 7'b0000011; // 11 - b
			7'b0001100: data_out = 7'b0100111; // 12 - c
			7'b0001101: data_out = 7'b0100001; // 13 - d
			7'b0001110: data_out = 7'b0000110; // 14 - e
			7'b0001111: data_out = 7'b0001110; // 15 - f
			default: data_out = 7'b0111111; // -
		
		endcase
	
	end

endmodule
