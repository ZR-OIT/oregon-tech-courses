`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Hayden Hutsell
// 
// Create Date:    17:24:24 01/24/2019 
// Design Name: 
// Module Name:    SSEG_output 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 1
// Revision 1 - mux that switches selects every clk cycle
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module SSEG_output(
	 input [15:0] digits,
	 input clk,
    output reg [7:0] SSEG_digit
    );
	 reg flag = 1'b1;
always @ (posedge clk) begin
		if (flag == 1'b1) begin
			SSEG_digit <= digits[7:0];
			flag <= ~flag;
		end
		else begin
			SSEG_digit <= digits[15:8];
			flag <= ~flag;
		end
end
endmodule
