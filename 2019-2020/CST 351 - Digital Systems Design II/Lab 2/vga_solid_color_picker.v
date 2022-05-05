`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date: 19:23:00 04/14/2020 
// Design Name: VGA Driver
// Module Name: vga_solid_color_picker
// Project Name: Lab2
// Target Devices: Cyclone V - DE1-SoC
// Tool versions: Quartus Lite 19.1
// Description: This module uses 4 switches to control half brightness, red, green, 
//						and blue color values.
//
// Dependencies:
//
// Revisions: 
// - Revision 0.01: File Created
// Additional Comments: Synchronous reset.
//
//////////////////////////////////////////////////////////////////////////////////

module vga_solid_color_picker(

	input [3:0] switches, // Input switches
	output reg [7:0] red, // 8-bit output color values
	output reg [7:0] green,
	output reg [7:0] blue

);
	
	initial begin // Initialize values for simulations
	
		red = 8'd0;
		green = 8'd0;
		blue = 8'd0;
	
	end
	
	always @ (switches) begin
		
		if(switches[2]) begin
			if(switches[3]) red = 8'd128;
			else red = 8'd255;
		end
		else red = 8'd0;
		
		if(switches[1]) begin
			if(switches[3]) green = 8'd128;
			else green = 8'd255;
		end
		else green = 8'd0;
		
		if(switches[0]) begin
			if(switches[3]) blue = 8'd128;
			else blue = 8'd255;
		end
		else blue = 8'd0;
		
	end

endmodule