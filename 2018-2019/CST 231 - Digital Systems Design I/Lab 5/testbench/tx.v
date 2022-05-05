`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:52:46 02/07/2019 
// Design Name: 
// Module Name:    tx 
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
//
//////////////////////////////////////////////////////////////////////////////////
module tx(
	input clk, // The 9600 Hz clock that you generated in task 1
	input go, // 1-bit input signal to tell the transmitter to transmit
	input [7:0] data, // The 8-bit data to be transmitted
	output reg dataout // 1-bit serial transmission output
	);

	// Declare state register
	reg		[1:0]state = 2'b0;
	reg		[3:0]count = 4'b0;
	// Declare states
	parameter start = 2'd0, shift = 2'd1, stop1 = 2'd2, stop2 = 2'd3;
	
	
	initial begin
		state = 2'd0;
		count = 4'd0;
	end
	
	always @ (posedge clk) begin
	
			case (state)
				start:
					if (go) //changed from !go to go
						state <= shift;
					else
						state <= start;
				shift:
					if (count != 4'd8)
					begin
						count <= count + 1;
						state <= shift;
					end
					else
					begin
						count <= 4'b0;
						state <= stop1;
					end
				stop1:
					begin
						state <= stop2;
					end
				stop2:
					begin
					state <= start;
					end
			endcase
	end
	
	// Determine the output based only on the current state
	// and the input (do not wait for a clock edge).
	always @ (state)
	begin
		case (state)
			start:
					if (!go)
						dataout <= 1'b0;
					else
						dataout <= 1'b1;
			shift:
				dataout <= data[count];	
			stop1:
				dataout <= 1'b1;
			stop2:
				dataout <= 1'b1;
			
		endcase
	end

endmodule
