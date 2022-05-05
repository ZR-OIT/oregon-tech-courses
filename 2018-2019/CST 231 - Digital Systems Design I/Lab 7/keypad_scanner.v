`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Oregon Tech
// Engineer: Zak Rowland
// 
// Create Date:    15:34:23 02/21/2019  
// Design Name: 	 Keypad scanner
// Module Name:    keypad_scanner
// Project Name: 		Lab7 - Keypad
// Target Devices: 	OwlBoard
// Tool versions: 
// Description: 	This module scan the keypad for button presses and outputs a
//						5-bit decoded binary value to be displayed.
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module keypad_scanner(
	
	input clk, //clock input - Use 1KHz or lower
	input [3:0] column, //4 columns as inputs - Pins 1 to 4
	output reg [3:0] row, //4 rows as outputs - Pins 5 to 8
	output reg [4:0] decoded //the decoded output is 5 bits

);

reg [4:0] state = 5'b00000; //state register 

parameter idle = 5'b00000, row_one = 5'b00001, row_two = 5'b00010,
				row_three = 5'b00100, row_four = 5'b01000, key_pressed = 5'b10000; //states


always @ (posedge clk) begin

	case(state)
		
		idle: begin
			decoded <= 5'b11111;
			state <= row_one;
		end
		
		row_one: begin //TOP ROW
			if(column[3] == 0) begin //LEFT COL
				//button pressed = 1
				decoded <= 5'b00001;
				state <= key_pressed;
			end
			else if(column[2] == 0) begin
				//button pressed = 2
				decoded <= 5'b00010;
				state <= key_pressed;
			end
			else if(column[1] == 0) begin
				//button pressed = 3
				decoded <= 5'b00011;
				state <= key_pressed;
			end
			else if(column[0] == 0) begin //RIGHT COL
				//button pressed = A
				decoded <= 5'b01010;
				state <= key_pressed;
			end
			else begin
				//no button pressed
				decoded <= 5'b11111;
				state <= row_two;
			end
		end
		
		row_two: begin
			if(column[3] == 0) begin //LEFT COL
				//button pressed = 4
				decoded <= 5'b00100;
				state <= key_pressed;
			end
			else if(column[2] == 0) begin
				//button pressed = 5
				decoded <= 5'b00101;
				state <= key_pressed;
			end
			else if(column[1] == 0) begin
				//button pressed = 6
				decoded <= 5'b00110;
				state <= key_pressed;
			end
			else if(column[0] == 0) begin //RIGHT COL
				//button pressed = B
				decoded <= 5'b01011;
				state <= key_pressed;
			end
			else begin
				//no button pressed
				decoded <= 5'b11111;
				state <= row_three;
			end
		end
		
		row_three: begin
			if(column[3] == 0) begin //LEFT COL
				//button pressed = 7
				decoded <= 5'b00111;
				state <= key_pressed;
			end
			else if(column[2] == 0) begin
				//button pressed = 8
				decoded <= 5'b01000;
				state <= key_pressed;
			end
			else if(column[1] == 0) begin
				//button pressed = 9
				decoded <= 5'b01001;
				state <= key_pressed;
			end
			else if(column[0] == 0) begin //RIGHT COL
				//button pressed = C
				decoded <= 5'b01100;
				state <= key_pressed;
			end
			else begin
				//no button pressed
				decoded <= 5'b11111;
				state <= row_four;
			end
		end
		
		row_four: begin //BOTTOM ROW
			if(column[3] == 0) begin //LEFT COL
				//button pressed = *
				decoded <= 5'b10000;
				state <= key_pressed;
			end
			else if(column[2] == 0) begin
				//button pressed = 0
				decoded <= 5'b10001;
				state <= key_pressed;
			end
			else if(column[1] == 0) begin
				//button pressed = #
				decoded <= 5'b10010;
				state <= key_pressed;
			end
			else if(column[0] == 0) begin //RIGHT COL
				//button pressed = D
				decoded <= 5'b01101;
				state <= key_pressed;
			end
			else begin
				//no button pressed
				decoded <= 5'b11111;
				state <= idle;
			end
		end
		
		key_pressed: begin
		
			if(column != 4'b1111) state <= key_pressed; //lockout
			else state <= idle;
		end
		
		default: begin
			decoded <= 5'b11111;
			state <= idle;
		end

	endcase

end

//always @ (posedge clk) begin
always @ (state) begin

	case(state)
	
		idle: begin
			row = 4'b1111;
		end
		row_one: begin //top row
			row = 4'b0111;
		end
		row_two: begin
			row = 4'b1011;
		end
		row_three: begin
			row = 4'b1101;
		end
		row_four: begin //bottom row
			row = 4'b1110;
		end
		key_pressed: begin
			row = 4'b0000;
		end
		default: begin
			row = 4'b1111;
		end
	
	endcase

end

endmodule 