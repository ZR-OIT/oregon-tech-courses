`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date: 19:02:00 05/01/2020 
// Design Name: 
// Module Name: button_debounce
// Project Name: Lab3_nios2
// Target Devices: Cyclone V - DE1-SoC
// Tool versions: Quartus Lite 18.1
// Description: Simple button debounce
//
// Dependencies:
//
// Revisions: 
// - Revision 0.01: File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

module button_debounce(

	input clk, // 50MHz input clock
	input button, // Input button, active low
	output reg button_state // Debounced output, active low

);

	parameter button_delay = 2500; // 50us delay at 50MHz
	
	reg [10:0] debounce_counter = 11'd0;
	
	initial begin
	
		button_state = 1'b1;
		debounce_counter = 11'd0;
	
	end
	
	always @ (posedge clk) begin
	
		if((button == 1'b0) && (debounce_counter >= button_delay)) begin
		
			button_state <= 1'b0;
			debounce_counter <= 11'd0;
		
		end
		else if(button == 1'b0) begin
		
			button_state <= 1'b1;
			debounce_counter <= debounce_counter + 11'd1;
		
		end
		else begin
		
			button_state <= 1'b1;
			debounce_counter <= 11'd0;
		
		end
		
	end

endmodule 