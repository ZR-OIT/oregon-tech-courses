`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Hayden Hutsell
// 
// Create Date:    14:27:39 02/11/2019 
// Design Name: 
// Module Name:    button_debounce_9600hz 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//need to test more, doesn't debounce letting go of button
//////////////////////////////////////////////////////////////////////////////////
module button_debounce_9600hz(
    input clk,
    input switch,
    output reg button_out
    );
	reg [6:0] debounce_count = 7'b0;
	
always @ (posedge clk) begin //debounces button, assuming 10ms actuation and 9600 hz clk
	if ((switch) && (debounce_count == 7'd96)) 
			begin
			button_out <= 1'b1;
			debounce_count <= 7'b0;
			end
	else if(switch)
		begin
			debounce_count <= debounce_count + 1'b1;
			button_out <= 1'b0;
		end
			else
		begin
			button_out <=0;
			debounce_count <= 7'b0;
		end
end
endmodule
