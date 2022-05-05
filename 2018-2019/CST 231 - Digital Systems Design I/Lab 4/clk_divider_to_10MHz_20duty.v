`timescale 1ns / 1ps

module clk_divider_to_10MHz_20duty( //based on 100MHz input clock
	input clk,
	input reset,
	output reg clk_div
);

parameter constantNum = 4'd10; //Count to 2 out of 10 for 10MHz at 20% duty cycle

reg [3:0] count; //4 bit counter

initial begin
	clk_div = 1'b0;
	count = 4'd0;
end

always @ (posedge clk or posedge reset) begin

	if(reset == 1'b1) begin
		count <= 4'd0;
		clk_div <= 1'b0;
	end
	else if(count >= 1'd0 && count < 2'd2) begin //if counter equals constant, invert clock and reset counter
		//clk_div <= ~clk_div;
		clk_div <= 1'b1;
		count <= count + 1'd1; 
	end
	else if(count >= 2'd2 && count < 4'd10) begin //if counter equals constant, invert clock and reset counter
		//clk_div <= ~clk_div;
		clk_div <= 1'b0;
		count <= count + 1'd1; 
	end
	else if(count == constantNum) count <= 4'd0;
	//else count <= count + 1'd1; //else add 1
end
endmodule
