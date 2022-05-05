`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date: 17:12:00 04/14/2020 
// Design Name: VGA Driver
// Module Name: clkdiv_50mhz_25mhz
// Project Name: Lab2
// Target Devices: Cyclone V - DE1-SoC
// Tool versions: Quartus Lite 19.1
// Description: This module divides a 50MHz clock signal to a 25MHz clock signal.
//
// Dependencies:
//
// Revisions: 
// - Revision 0.01: File Created
// Additional Comments: Synchronous reset.
//
//////////////////////////////////////////////////////////////////////////////////

module clkdiv_50mhz_25mhz(

	input clk_in, // Base clock 
	input reset, // Reset signal 
	output reg clk_out // Divided clock output
	
);

	// 50MHz / 25MHz = 2 -> 2 / 2 = 1
	parameter count_to = 1'b1; // Count to 1 for 25MHz at 50% duty cycle.
	reg counter; // Number of bits = floor(log(count_to)/log(2)) + 1

	initial begin // Initialize values for simulations

		clk_out = 1'b0;
		counter = 1'b0;

	end

	always @ (posedge clk_in) begin
		
		if(reset == 1'b1) begin
			clk_out = 1'b0; // Reset values
			counter = 1'b0;
		end
		else if (counter == count_to) begin
			clk_out <= 1'b0; // Output clock is low
			counter <= 1'b0; // Reset counter
		end
		else begin
			clk_out <= 1'b1; // Output clock is high
			counter <= 1'b1; // Increment counter
		end
		
	end

endmodule	