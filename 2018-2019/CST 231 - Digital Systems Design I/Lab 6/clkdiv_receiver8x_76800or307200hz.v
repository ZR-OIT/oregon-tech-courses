`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Tech
// Engineer: Zak Rowland
// 
// Create Date:		Feb 2019 
// Design Name:		UART Receiver variable clk divider
// Module Name:		clkdiv_receiver8x_76800or307200hz 
// Project Name:		Lab6
// Target Devices:	Spartan 6
// Tool versions: 
// Description: 		This module receives divides a 48mhz clk down to 9600x8hz or 
//							upon button press down to 38400x8hz
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module clkdiv_receiver8x_76800or307200hz(
input clk_in,								 
input button,
output reg led,
output reg clk_out
);

parameter baud_76800 = 9'd312; //rounded down
parameter baud_307200 = 7'd78; //rounded down

reg [8:0] count;


always @ (posedge clk_in) begin
	led <= button;
	case (button)
		1'b0: begin 
			if (count == baud_76800) begin
				clk_out <= ~clk_out;
				count <= 9'd0;
			end
			else count <= count + 1'b1;
		end
		1'b1: begin
			if (count == baud_307200) begin
				clk_out <= ~clk_out;
				count <= 9'd0;
			end
			else count <= count + 1'b1;
			end
	endcase
end
endmodule	