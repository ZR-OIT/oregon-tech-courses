`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Tech
// Engineer: Zak Rowland and Hayden Hutsell
// 
// Create Date:		16:10:37 02/14/2019 
// Design Name:		UART Receiver
// Module Name:		rx 
// Project Name:		Lab6
// Target Devices:	Spartan 6
// Tool versions: 
// Description: 		This module receives serial data in including a start bit,
//							8 bits of data, and 2 stop bits all checked with even parity.
//							The data is then output to a decoder for display.
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module rx(
    input data_in, 			//serial data in
    input clk,					//8x or 16x receiver clock
	 output reg parity_led,		//if parity led is lit, even parity failed
    output reg data_ready,		//indicates that data is available from the receiver
    output reg [7:0] data_out	//output to decoder for sseg display
    );
	
	reg [2:0] state = 3'b0;				//state register
	reg [3:0] count = 4'b0;				//counter
	reg [4:0] delay_count = 5'b0;		//used to delay execution, for timing
	reg [7:0] received_data = 8'b0;	//data bits received from data_in
	reg received_parity = 1'b0;			//store received parity bit
	reg calculated_parity = 1'b0;			//tracks calculated parity
	
	parameter idle = 0, receive = 1, even_parity = 2, stop_delay = 3, delay_8 = 4, delay_3 = 5, parity_delay = 6;
	
	always @ (posedge clk) begin
	
		case (state)
			idle:
				begin
				data_ready <= 1'b0; //reset data rdy line
					if(data_in == 1'b0) state <= delay_3; //received a 0, go to delay 3 and check for 0 again					
					
					else state <= idle; //if no 0, stay in idle								
				end
			receive:
				begin
					if (count != 4'd8) begin
						received_data[count] <= data_in; //receive 8 data bits, delaying for 8 clk cycles after each one
						count <= count + 1'b1;
						state <= delay_8;
					end
					else begin
						count <= 4'd0; //after we have received all the bits, reset counter and prepare to receive the parity bit
						state <= parity_delay;	
					end
				end
			even_parity:
				begin
					received_parity <= data_in; //receive even parity bit
					calculated_parity <= ^received_data; //xor the received data
					
					if(received_parity != calculated_parity) begin //if they are different, light up the led, go to stop delay, put the received data to the data_out
						parity_led <= 1'b1;
						data_out <= received_data;
						state <= stop_delay;
					end
					else begin
						parity_led <= 1'b0; //if theyre the same, turn the led off, put the received data to the data_out
						data_out <= received_data;
						state <= stop_delay;
					end
				end
			stop_delay://these states delay for various amounts of cycles, as we are super sampling at 8x
				begin
					data_ready <= 1'b1; //while we are delaying for the stop bits, nows a good time to say our data is ready, until we go back to idle
					 
					if(delay_count != 5'd18) begin
						delay_count <= delay_count + 1'b1;
						state <= stop_delay;
					end
					else begin
						delay_count <= 4'b0;
						state <= idle;
					end
				end
			delay_8:
				begin
					if(delay_count != 4'd6) begin
						delay_count <= delay_count + 1'b1;
						state <= delay_8;
					end
					else begin
						delay_count <= 4'b0;
						state <= receive;
					end
				end
			parity_delay:
				begin
					if(delay_count != 4'd6) begin
						delay_count <= delay_count + 1'b1;
						state <= parity_delay;
					end
					else begin
						delay_count <= 4'b0;
						state <= even_parity;
					end
				end		
			delay_3:
				begin
					if(delay_count != 4'd2) begin
						delay_count <= delay_count + 1'b1;
						state <= delay_3;
					end
					else begin
						delay_count <= 4'b0;
						if (data_in <= 1'b0)state <= delay_8;
						else state <= idle;
					end
				end
		endcase
	end

endmodule
