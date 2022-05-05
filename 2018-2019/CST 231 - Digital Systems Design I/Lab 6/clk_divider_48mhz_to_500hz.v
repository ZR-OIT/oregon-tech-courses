`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Hayden Hutsell
// 
// Create Date:    16:33:43 01/24/2019 
// Design Name: 
// Module Name:    clk_divider_48mhz_to_500hz 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 1
// Revision converts 48mhz clk to 500hz
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module clk_divider_48mhz_to_500hz(
    input CLK,
    output reg divided_CLK
    );
reg [15:0] count = 16'b0000000000000000;

always @ (posedge CLK) begin

	if (count == 16'b1011001110101111)begin //covers 48000 values
		divided_CLK <= ~divided_CLK;
		count <= 16'b0000000000000000;
	end
else count <= count + 16'b0000000000000001;

end
endmodule

