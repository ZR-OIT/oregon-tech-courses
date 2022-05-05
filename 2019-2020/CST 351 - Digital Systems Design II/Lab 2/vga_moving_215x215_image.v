`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date: 18:33:00 04/28/2020 
// Design Name: VGA Driver
// Module Name: vga_moving_215x215_image
// Project Name: Lab2
// Target Devices: Cyclone V - DE1-SoC
// Tool versions: Quartus Lite 19.1
// Description: This module drives a moving 215x215 image on 640x480 resolution.
//
// Dependencies:
//
// Revisions: 
// - Revision 0.01: File Created
// Additional Comments: Animation help from:
//									https://timetoexplore.net/blog/arty-fpga-vga-verilog-01
//
//////////////////////////////////////////////////////////////////////////////////

module vga_moving_215x215_image(

	input clk_in, // 25MHz clock signal
	input animate, // Animate signal
	input [9:0] h_pixel, // Current horizontal pixel position
	input [8:0] v_line, // Current vertical line position
	input [7:0] color_data_from_rom, // 3-2-2 RGB color data from ROM
	output [15:0] address_to_rom, // Address to read color data from ROM
	output reg [7:0] red, // 8-bit color values
	output reg [7:0] green,
	output reg [7:0] blue

);
	
	parameter horizontal_image_size = 215; // 215x215 image
	parameter vertical_image_size = 215;
	parameter half_horizontal_image_size = 108;
	parameter half_vertical_image_size = 108;
	parameter h_resolution = 640; // 640x480 resolution display area
	parameter v_resolution = 480;
	parameter total_pixels = horizontal_image_size * vertical_image_size; // Total pixels of image 215x215 image == 46,225
	parameter h_start = 144; // After front porch, sync, and back porch
	parameter h_end = 784; // End of row
	parameter v_start = 35; // After front porch, sync, and back porch
	parameter v_end = 515; // End of frame
	
	reg [15:0] counter = 16'd0; // Counter for total pixels of images drawn
	reg [9:0] x_pos = half_horizontal_image_size + 1; // Initial position in top left corner
	reg [8:0] y_pos = half_vertical_image_size + 1;
	wire [9:0] left_edge; // Track the left edge of the image (x)
	wire [9:0] right_edge; // Track the right edge of the image (x)
	wire [8:0] top_edge; // Track the top edge of the image (y)
	wire [8:0] bottom_edge; // Track the bottom edge of the image (y)
	reg x_dir = 1'b1; // Direction image is travelling horizontally, 1 for right 0 for left
	reg y_dir = 1'b1; // Direction image is travelling vertically, 1 for down 0 for up
	
	assign left_edge = x_pos - half_horizontal_image_size;
	assign right_edge = x_pos + half_horizontal_image_size;
	assign top_edge = y_pos - half_vertical_image_size;
	assign bottom_edge = y_pos + half_vertical_image_size;
	
	assign address_to_rom = counter;
	
	always @ (posedge clk_in) begin
		
		if(animate) begin // If the vga driver sent the animate pulse 
		
			x_pos <= (x_dir) ? x_pos + 10'd1 : x_pos - 10'd1; // Adjust horizontal postion by 1 pixel based on x dir
			y_pos <= (y_dir) ? y_pos + 9'd1 : y_pos - 9'd1; // Adjust vertical position by 1 line based on y dir
			
			if(x_pos <= (half_horizontal_image_size + h_start + 1)) x_dir <= 1'b1; // Image about to hit left edge of viewing area
			
			if(x_pos >= (h_end - half_horizontal_image_size - 1)) x_dir <= 1'b0; // Image about to hit right edge of viewing area
			
			if(y_pos <= (v_start + half_vertical_image_size + 1)) y_dir <= 1'b1; // Image about to hit top edge of viewing area
			
			if(y_pos >= (v_end - half_vertical_image_size - 1)) y_dir <= 1'b0; // Image about to hit bottom edge of viewing area
		
		end
		
		if((h_pixel > left_edge) && (v_line > top_edge) && (h_pixel < right_edge) && (v_line < bottom_edge)) begin // If within image edges, draw the image
				
			red[4:0] <= 5'd0; // Pad with 5 zeroes
			red[7:5] <= color_data_from_rom[7:5]; // 3-bit red from ROM
			green[4:0] <= 5'd0; // Pad with 5 zeroes
			green[7:5] <= color_data_from_rom[4:2]; // 3-bit green from ROM
			blue[5:0] <= 6'd0; // Pad with 6 zeroes
			blue[7:6] <= color_data_from_rom[1:0]; // 2-bit blue from ROM
				
			if(counter >= total_pixels - 1) counter <= 16'd0; // If all pixels of image have been drawn, restart
			else counter <= counter + 16'd1; // Otherwise keeping drawing image pixels
				
		end
		else begin // Draw black
			
			red <= 8'd0;
			green <= 8'd0;
			blue <= 8'd0;
			
		end
	
	end
	
endmodule