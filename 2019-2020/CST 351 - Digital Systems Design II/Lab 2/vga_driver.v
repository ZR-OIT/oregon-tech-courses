`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date: 19:23:00 04/14/2020 
// Design Name: VGA Driver
// Module Name: vga_driver
// Project Name: Lab2
// Target Devices: Cyclone V - DE1-SoC
// Tool versions: Quartus Lite 19.1
// Description: This module drives a 25MHz VGA signal at 640x480 resolution.
//
// Dependencies:
//
// Revisions: 
// - Revision 0.01: File Created
// Additional Comments: Synchronous reset.
//
//////////////////////////////////////////////////////////////////////////////////

module vga_driver(

	input clk_in, // 25MHz pixel clock
	input reset, // Reset signal
	output hsync, // Horizontal sync
	output vsync, // Vertical sync
	output in_display_area, // Signal is high if drawing a pixel in viewing area
	output reg [9:0] h_count,
	output reg [8:0] v_count,
	output animation
	
);
	
	// Timing parameters based on 640x480 resolution with a 25MHz pixel clock
	
	parameter h_sync_time = 96; // Horizontal sync width in pixels (3.813us)
	parameter h_backporch_time = 48; // Horizontal back porch time in pixels (1.907us)
	parameter h_frontporch_time = 16; // Horizontal front porch time in pixels (0.636us)
	parameter h_view_time = 640; // Horizontal viewing area in pixels (25.422us)
	parameter h_lr_border = 0; // Horizontal left and right border in pixels
	parameter h_total_time = (h_sync_time + h_backporch_time + h_frontporch_time + h_view_time + h_lr_border); // Total horizontal time in pixels
	parameter v_sync_time = 2; // Vertical sync width in lines (0.064ms)
	parameter v_backporch_time = 33; // Vertical back porch time in lines (1.048ms)
	parameter v_frontporch_time = 10; // Vertical front porch time in lines (0.318ms)
	parameter v_view_time = 480; // Vertical viewing area in lines (12.253ms)
	parameter v_tb_border = 0; // Vertical top and bottom border in lines
	parameter v_total_time = (v_backporch_time + v_frontporch_time + v_view_time + v_tb_border); // Total vertical time in lines
	
	assign hsync = (h_count < h_sync_time); // Generate horizontal sync signal
	assign vsync = (v_count < v_sync_time); // Generate vertical sync signal
	
	assign in_display_area = ((h_count >= 144 && h_count < 784) && (v_count >= 35 && v_count < 515)); // Generate display area signal
	
	assign animation = ((v_count == v_view_time - 1) & (h_count == h_total_time)); // Generate animation signal at end of frame
	
	initial begin // Initialize values for simulations

		h_count = 10'd0;
		v_count = 9'd0; 

	end

	
	always @ (posedge clk_in) begin
	
		
		if(reset == 1'b1) h_count <= 10'd0;
		else if(h_count == h_total_time) h_count <= 10'd0;
		else h_count <= h_count + 10'd1;
	
	end
	
	always @ (posedge clk_in) begin
	
		if(reset == 1'b1) v_count <= 9'd0;
		else if(h_count == h_total_time) begin
		
			if(v_count == v_total_time) v_count <= 9'd0;
			else v_count <= v_count + 9'd1;
		
		end
	
	end
	
endmodule