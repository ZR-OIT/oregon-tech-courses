`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:				Oregon Institute of Technology
// Engineer:			Zak Rowland
// 
// Create Date:    	13:39:28 03/19/2019 
// Design Name: 		Pulse Width Modulation RGB LED Control 
// Module Name:    	counter 
// Project Name: 		Lab8
// Target Devices: 	OwlBoard
// Tool versions: 
// Description: 		This modules runs an up/down counter that is used to generate variable PWM,
//							as well as switching colors when necessary.
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module counter(
    input clk,
	 input pwm_signal,
    output reg [3:0] count_out,
	 output reg red,
	output reg green,
	output reg blue
    );

reg count_dir = 1; //1 for up, 0 for down
reg [2:0] current_color = 3'b100;
parameter rgb_red = 3'b100, rgb_green = 3'b010, rgb_blue = 3'b001, rgb_off = 3'b000;

always @ (posedge clk) begin
	
	if(count_dir == 1'b1) begin //if counting up
		if(count_out == 4'd15) count_dir <= 1'b0; //if max count, switch to count down
		else begin
			count_dir <= 1'b1;
			count_out <= count_out + 4'd1; //increment count
		end
	end
	
	else begin //if counting down
		if(count_out == 4'd0) begin //if minimum count, switch to count up and change color
		
			count_dir <= 1'b1;
			
			if(current_color == rgb_red) current_color <= rgb_green; //if currently red, switch to green
			else if(current_color == rgb_green) current_color <= rgb_blue; //if currently green, switch to blue
			else if(current_color == rgb_blue) current_color <= rgb_red; //if currently blue, switch to red
			else current_color <= rgb_red;
		
		end
		else begin
			count_dir <= 1'b0;
			count_out <= count_out - 4'd1; //decrement count
		end
	end
end

always @ (*) begin //controls RGB depending on current color

	case(current_color)
	
	rgb_red: begin
		red = pwm_signal;
		green = 1'b0;
		blue = 1'b0;
	
	end
	rgb_green: begin
		red = 1'b0;
		green = pwm_signal;
		blue = 1'b0;
	
	end
	rgb_blue: begin
		red = 1'b0;
		green = 1'b0;
		blue = pwm_signal;
	
	end
	rgb_off: begin
		red = 1'b0;
		green = 1'b0;
		blue = 1'b0;
	end
	
	default: begin
		red = 1'b0;
		green = 1'b0;
		blue = 1'b0;
	end
	
	endcase
	
end

endmodule
