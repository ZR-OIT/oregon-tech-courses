`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Hayden Hutsell
// 
// Create Date:    17:10:50 01/24/2019 
// Design Name: 
// Module Name:    SSEG_sel 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 1
// Revision: Anode selector for the sseg
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module SSEG_sel(
    output reg [1:0] SSEGA,
    input clk_500hz
    );
	reg flag;
always @ (posedge clk_500hz) begin
	if (flag) begin
		SSEGA <= 2'b10;
		flag <= ~flag;
		end
	else begin
		SSEGA <= 2'b01;
		flag <= ~flag;
		end
	end
endmodule
