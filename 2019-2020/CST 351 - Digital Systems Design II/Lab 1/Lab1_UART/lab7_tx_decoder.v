`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Zak Rowland
// 
// Create Date:    12:22:33 02/26/2019 
// Design Name: 
// Module Name:    tx_decoder 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: Send this module a 5 bit value, and it will output a single character to 
// 					the tx_driver module when a button has been pressed.
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
// 
//
//////////////////////////////////////////////////////////////////////////////////
module tx_decoder(
    input clk,
    input [4:0] data,
	 output reg go,
    output reg [7:0] tx_character
);
	
	reg [3:0] delay_count = 4'b0000;
	reg [4:0] current_data = 5'b00000;
	
	// Declare state register
	reg [1:0]state = 2'b00;
	
	// Declare states
	parameter idle = 0, tx_char_transmit = 1, delay = 2;
	
	always @ (posedge clk) begin
	
			case (state)
				idle:
					if (data == 5'b00000)
					begin
						state <= idle;
						go <= 1'd0; //if button hasn't been pressed, idle
					end
					else
					begin
						current_data <= data;
						state <= tx_char_transmit; // else, begin transmitting first character
					end
				tx_char_transmit:
					begin
						case(current_data)	
							5'b10001: tx_character <= 8'b00110000; //0
							5'b00001: tx_character <= 8'b00110001; //1
							5'b00010: tx_character <= 8'b00110010; //2
							5'b00011: tx_character <= 8'b00110011; //3
							5'b00100: tx_character <= 8'b00110100; //4
							5'b00101: tx_character <= 8'b00110101; //5
							5'b00110: tx_character <= 8'b00110110; //6
							5'b00111: tx_character <= 8'b00110111; //7
							5'b01000: tx_character <= 8'b00111000; //8
							5'b01001: tx_character <= 8'b00111001; //9
							5'b01010: tx_character <= 8'b01000001; //10 - A
							5'b01011: tx_character <= 8'b01000010; //11 - B
							5'b01100: tx_character <= 8'b01000011; //12 - C
							5'b01101: tx_character <= 8'b01000100; //13 - D
							5'b10000: tx_character <= 8'b00101010; //*
							5'b10010: tx_character <= 8'b00100011; //#
							5'b11111: tx_character <= 8'b00100000; //space
							default:  tx_character <= 8'b00100000;
						endcase
						
						delay_count <= 4'd0; //reset delay counter
						state <= delay; //go to delay state
						go <= 1'b1; //send go signal to tx_driver
					end
				delay:
					if (delay_count != 4'd12) begin
							delay_count <= delay_count + 4'd1; //delay for 12 cycles, as it takes that many cycles to output a letter through UART
							state <= delay;
						end
						else begin
							go <= 1'b0;
							delay_count <= 4'd0;
							if(current_data == data) state <= delay; 
							else begin
								current_data <= 5'b00000;
								state <= idle;
							end
						end
			endcase
	end
endmodule
