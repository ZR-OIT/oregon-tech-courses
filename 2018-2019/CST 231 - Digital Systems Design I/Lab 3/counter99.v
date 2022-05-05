`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Institute of Technology
// Engineer: Zak Rowland
// 
// Create Date:    14:24:10 01/28/2019 
// Design Name: 	Seven segment display test 
// Module Name:    counter99 
// Project Name: 	Lab3
// Target Devices: 	OwlBoard
// Tool versions: 
// Description: 	This module uses two seperate registers to count from 0-99.
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module counter99(
	input clk,
	output reg [3:0] count_out_dig_one,
	output reg [3:0] count_out_dig_two
);

always @ (posedge clk) begin
	if(count_out_dig_two == 4'd9 && count_out_dig_one == 4'd9) begin //if both digits 9, reset to 0
		count_out_dig_one <= 4'd0;
		count_out_dig_two <= 4'd0;
	end
	else if(count_out_dig_one == 4'd9) begin //if right digit is 9, reset right digit to 0 and increment left digit
		count_out_dig_one <= 4'd0;
		count_out_dig_two <= count_out_dig_two + 4'd1;
	end
	else count_out_dig_one <= count_out_dig_one + 4'd1; //increment right digit
end
endmodule
