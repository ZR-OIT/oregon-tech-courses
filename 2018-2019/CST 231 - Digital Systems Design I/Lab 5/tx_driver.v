`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Hayden Hutsell / Zak Rowland
// 
// Create Date:    11:47:33 02/11/2019 
// Design Name: 
// Module Name:    tx_driver 
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
// Send this module a reversed 10 character message, and it will output a single character to 
// the tx message module one at a time when a button has been pressed
//
//////////////////////////////////////////////////////////////////////////////////
module tx_driver(
    input clk,
    input [79:0] message,
    input switch,
	 output reg go,
    output reg [7:0] tx_character
    );
	
	reg [3:0] delay_count = 4'b0;
	
	
// Declare state register
	reg [1:0]state = 2'b0;
	reg [6:0] char_letter_count = 7'd8;
	// Declare states
	parameter idle = 0, tx_char_transmit = 1, delay = 2;
	
	always @ (posedge clk) begin
	
			case (state)
				idle:
					if (!switch)
					begin
						state <= idle;
						go <= 1'd0; //if button hasn't been pressed, idle
					end
					else
					begin
						state <= tx_char_transmit; // else, begin transmitting first character
					end
				tx_char_transmit:
					begin
						tx_character <= message[(char_letter_count - 1'b1) -:8]; //takes the index of the bits outputted already -1 down to the index minus 8
						char_letter_count <= char_letter_count + 4'd8; //8bits (one char) transmitted
						delay_count <= 4'b0; //reset delay counter
						state <= delay; //go to delay state
						go <= 1'b1; //send go signal to tx module
					end
				delay:
						if (delay_count != 4'd12) begin
							delay_count <= delay_count + 4'd1; //delay for 12 cycles, as it takes that many cycles to output a letter through UART
							state <= delay;
							end
						else
						begin
							if (char_letter_count == 7'd88)
							begin
								char_letter_count <= 4'd0; //if we have transmitted all of the characters, go back to idle
								state <= idle;
								go <= 1'd0; 
							end
							else
							begin
							state <= tx_char_transmit;
							go <= 1'b0; //else, go transmit the next character
							end
					end
			endcase
	end 
endmodule	
	// Determine the output based only on the current state
	// and the input (do not wait for a clock edge).
	
