`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date: 14:05:00 04/28/2020 
// Design Name: VGA Driver
// Module Name: vga_215x215_image
// Project Name: Lab2
// Target Devices: Cyclone V - DE1-SoC
// Tool versions: Quartus Lite 19.1
// Description: This module drives a 215x215 image on 640x480 resolution.
//
// Dependencies:
//
// Revisions: 
// - Revision 0.01: File Created
// Additional Comments:
//
//////////////////////////////////////////////////////////////////////////////////

module vga_215x215_image(

	input clk_in, // 25MHz clock signal
	input [9:0] h_pixel, // Current horizontal pixel position
	input [8:0] v_line, // Current vertical line position
	input [7:0] color_data_from_rom, // 3-2-2 RGB color data from ROM
	output [15:0] address_to_rom, // Address to read color data from ROM
	output reg [7:0] red, // 8-bit color values
	output reg [7:0] green,
	output reg [7:0] blue

);
	
	parameter image_size = 215;
	parameter h_start = 344; // 640
	parameter h_end = h_start + image_size;
	parameter v_start = 180; // 480
	parameter v_end = v_start + image_size;
	parameter total_pixels = image_size * image_size;
	
	wire [7:0] color_data;
	wire in_image_area;
	reg [15:0] counter = 16'd0;
	reg initialized = 1'b0;
	
	assign in_image_area = ((h_pixel >= h_start && h_pixel < h_end) && (v_line >= v_start && v_line < v_end));
	
	assign address_to_rom = counter;
	assign color_data = color_data_from_rom;
	
	always @ (posedge clk_in) begin
	
		if(initialized == 1'b1) begin
		
			if(in_image_area) begin // Draw image
				
				red[4:0] <= 5'd0;
				red[7:5] <= color_data[7:5];
				green[4:0] <= 5'd0;
				green[7:5] <= color_data[4:2];
				blue[5:0] <= 6'd0;
				blue[7:6] <= color_data[1:0];
				
				if(counter >= total_pixels - 1) counter <= 16'd0;
				else counter <= counter + 16'd1;
				
			end
			else begin // Draw black
			
				red <= 8'd0;
				green <= 8'd0;
				blue <= 8'd0;
				
				if(counter >= total_pixels - 1) counter <= 16'd0;
			
			end
		end
		else begin // Initialize values
		
			counter <= 16'd0;
			red <= 8'd0;
			green <= 8'd0;
			blue <= 8'd0;
			initialized <= 1'b1;
			
		end
		
	
	end
	
endmodule