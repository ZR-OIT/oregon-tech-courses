`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date: 19:37:00 04/23/2020 
// Design Name: VGA Driver
// Module Name: vga_driver
// Project Name: Lab2
// Target Devices: Cyclone V - DE1-SoC
// Tool versions: Quartus Lite 19.1
// Description: This module drives a 4x4 cross hatch pattern at 640x480 resolution.
//
// Dependencies:
//
// Revisions: 
// - Revision 0.01: File Created
// Additional Comments:
//
//////////////////////////////////////////////////////////////////////////////////

module vga_cross_hatch(
	
	input clk_in, // 25MHz clock signal
	input [9:0] h_pixel, // Current horizontal pixel position
	input [8:0] v_line, // Current vertical line position
	output reg [7:0] red, // 8-bit color values
	output reg [7:0] green,
	output reg [7:0] blue
	
);
	
	parameter h_start = 144; // 640
	parameter h_quarter = 304;
	parameter h_middle = 464;
	parameter h_three_quarter = 624;
	parameter h_end = 784;
	
	parameter v_start = 35; // 480
	parameter v_quarter = 155;
	parameter v_middle = 275;
	parameter v_three_quarter = 395;
	parameter v_end = 515;
	
	wire red_zone;
	wire blue_zone;
	
	assign red_zone = ((h_pixel >= h_start && h_pixel < h_quarter) && (v_line >= v_start && v_line < v_quarter)) || // Row 1
							((h_pixel >= h_middle && h_pixel < h_three_quarter) && (v_line >= v_start && v_line < v_quarter)) ||
							
							((h_pixel >= h_quarter && h_pixel < h_middle) && (v_line >= v_quarter && v_line < v_middle)) || // Row 2
							((h_pixel >= h_three_quarter && h_pixel < h_end) && (v_line >= v_quarter && v_line < v_middle)) ||
							
							((h_pixel >= h_start && h_pixel < h_quarter) && (v_line >= v_middle && v_line < v_three_quarter)) || // Row 3
							((h_pixel >= h_middle && h_pixel < h_three_quarter) && (v_line >= v_middle && v_line < v_three_quarter)) ||
							
							((h_pixel >= h_quarter && h_pixel < h_middle) && (v_line >= v_three_quarter && v_line < v_end)) || // Row 4
							((h_pixel >= h_three_quarter && h_pixel < h_end) && (v_line >= v_three_quarter && v_line < v_end));
	
	assign blue_zone = ((h_pixel >= h_quarter && h_pixel < h_middle) && (v_line >= v_start && v_line < v_quarter)) || // Row 1
								((h_pixel >= h_three_quarter && h_pixel < h_end) && (v_line >= v_start && v_line < v_quarter)) ||
								
								((h_pixel >= h_start && h_pixel < h_quarter) && (v_line >= v_quarter && v_line < v_middle)) || // Row 2
								((h_pixel >= h_middle && h_pixel < h_three_quarter) && (v_line >= v_quarter && v_line < v_middle)) ||
								
								((h_pixel >= h_quarter && h_pixel < h_middle) && (v_line >= v_middle && v_line < v_three_quarter)) || // Row 3
								((h_pixel >= h_three_quarter && h_pixel < h_end) && (v_line >= v_middle && v_line < v_three_quarter)) ||
								
								((h_pixel >= h_start && h_pixel < h_quarter) && (v_line >= v_three_quarter && v_line < v_end)) || // Row 4
								((h_pixel >= h_middle && h_pixel < h_three_quarter) && (v_line >= v_three_quarter && v_line < v_end));
	
	initial begin // Initialize values for simulations
	
		red = 8'd0;
		green = 8'd0;
		blue = 8'd0;
	
	end
	
	always @ (posedge clk_in) begin
	
		if(red_zone) begin
			red <= 8'd255;
			green <= 8'd0;
			blue <= 8'd0;
		end
		else if(blue_zone) begin
			red <= 8'd0;
			green <= 8'd0;
			blue <= 8'd255;
		end
		else begin
			red <= 8'd0;
			green <= 8'd0;
			blue <= 8'd0;
		end
	end
	
endmodule