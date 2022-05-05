`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Tech
// Engineer: Zak Rowland
// 
// Create Date:    15:34:23 02/21/2019  
// Design Name: 	 48MHz clock divider to 1KHz
// Module Name:    clkdiv_48MHz_to_1KHz
// Project Name: 		Lab7 - Keypad
// Target Devices: 	OwlBoard
// Tool versions: 
// Description: 	This module receives the OwlBoard's 48MHz clock signal and
//						divides it down to 1KHz at 50% duty. Used by the keypad scanner.
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module clkdiv_48MHz_to_1KHz(
    input clk,
    output reg clk_div
    );

// 48MHz / 1KHz = 48,000 -> 48,000 / 2 = 24,000
// floor of log(24000) / log(2) + 1 = 15 bits
parameter constantNum = 15'd24000; //count to 24,000 for 1KHz at 50% duty cycle

reg [14:0] count; //15 bit counter

always @ (posedge clk) begin

	if(count == constantNum) begin //if counter equals constant, invert clock and reset counter
		count <= 15'd0;
		clk_div <= ~clk_div;
	end
	else count <= count + 1'd1; //else add 1 to count

end

endmodule
