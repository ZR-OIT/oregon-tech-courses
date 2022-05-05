`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date: 17:02:00 04/14/2020 
// Design Name: VGA Driver
// Module Name: lab2_top
// Project Name: Lab2
// Target Devices: Cyclone V - DE1-SoC
// Tool versions: Quartus Lite 19.1
// Description: This modules controls all other modules to drive a VGA signal.
//
// Dependencies:
//
// Revisions: 
// - Revision 0.01: File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

module lab2_top(

	input CLOCK_50, // 50MHz base clock
	input [9:0] SW, // 10 input switches
	output [9:0] LEDR, // 10 output LEDs
	output [7:0] VGA_R, // 8-bit red signal to VGA DAC
	output [7:0] VGA_G, // 8-bit green signal to VGA DAC
	output [7:0] VGA_B, // 8-bit blue signal to VGA DAC
	output VGA_CLK, // VGA pixel clock
	output VGA_HS, // VGA horizontal sync signal
	output VGA_VS, // VGA vertical sync signal
	output VGA_SYNC_N, // Active low VGA sync signal, for a composite sync, tied LOGIC low when not in use
	output VGA_BLANK_N // Active low VGA blank signal, high during: front porch + sync + back porch
	
);
	
	wire clk_25MHz;
	wire in_display;
	wire [9:0] h_position;
	wire [8:0] v_position;
	wire [15:0] rom_address;
	wire [7:0] rom_output;
	
	wire animation_signal;
	
	assign LEDR[9:0] = SW[9:0];

	assign VGA_CLK = clk_25MHz;
	assign VGA_SYNC_N = 1'b1;
	assign VGA_BLANK_N = in_display;
	
	clkdiv_50mhz_25mhz clkdiv_25MHz(.clk_in(CLOCK_50), .reset(SW[9]), .clk_out(clk_25MHz));
	vga_driver vga_driver_instance(.clk_in(clk_25MHz), .reset(SW[9]), .hsync(VGA_HS), .vsync(VGA_VS), .in_display_area(in_display), .h_count(h_position), .v_count(v_position), .animation(animation_signal));
	//vga_solid_color_picker vga_color_instance(.switches(SW[3:0]), .red(VGA_R), .green(VGA_G), .blue(VGA_B));
	//vga_cross_hatch vga_hatch_instance(.clk_in(clk_25MHz), .h_pixel(h_position), .v_line(v_position), .red(VGA_R), .green(VGA_G), .blue(VGA_B));
	image_rom image_data(.address(rom_address), .clock(clk_25MHz), .q(rom_output));
	//vga_215x215_image drive_image(.clk_in(clk_25MHz), .h_pixel(h_position), .v_line(v_position), .color_data_from_rom(rom_output), .address_to_rom(rom_address), .red(VGA_R), .green(VGA_G), .blue(VGA_B));
	vga_moving_215x215_image drive_image(.clk_in(clk_25MHz), .animate(animation_signal), .h_pixel(h_position), .v_line(v_position), .color_data_from_rom(rom_output), .address_to_rom(rom_address), .red(VGA_R), .green(VGA_G), .blue(VGA_B));
	
endmodule
