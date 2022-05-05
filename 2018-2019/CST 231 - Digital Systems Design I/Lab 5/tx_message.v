`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Hayden Hutsell / Zak Rowland 
// 
// Create Date:    10:26:33 02/11/2019 
// Design Name: 
// Module Name:    tx_message 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision - 1 
// Additional Comments: send this module 8 data bits, and it will output a go bit, 8
//						data bits, even parity, and 2 stop bits
//
//////////////////////////////////////////////////////////////////////////////////
module tx_message(
    input clk,
	 input [7:0] datain,
    output reg dataout,
    input go
    );

	// Declare state register
	reg		[2:0]state = 2'b0;
	reg [3:0] count = 8'b0;
	// Declare states
	parameter start = 0, shift = 1, stop1 = 2, stop2 = 3, even_parity = 4;
	
	always @ (posedge clk) begin
	
			case (state)
				start:
					if (go)
					begin
						state <= shift;
						dataout <= 1'b0; //if we receive go signal, start shifting
					end
					else
					begin
						state <= start; //else, idle
						dataout <= 1'b1;
					end
				shift:
					if (count != 4'd8)
					begin
						dataout <= datain[count];
						count <= count + 4'd1; //shift until 8 bits have shifted
						state <= shift;
					end
					else
					begin
						count <= 4'b0;
						state <= even_parity; //after 8 bits shifted, go to even parity
					end
				stop1:
					begin
						dataout <= 1'b1;
						state <= stop2; //output 1st stop bit
					end
				stop2:
					begin
					dataout <= 1'b1;
					state <= start; //output second stop bit
					end
				even_parity:
					begin
					dataout <= ^datain;
					state <= stop1; // xnor for even parity
					end
			endcase
	end
endmodule

