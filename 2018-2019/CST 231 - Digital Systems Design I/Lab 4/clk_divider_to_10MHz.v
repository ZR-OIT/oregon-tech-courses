`timescale 1ns / 1ps

module clk_divider_to_10MHz( //based on 100MHz input clock
	input clk,
	input reset,
	output reg clk_div
);

parameter constantNum = 3'd5; //Count to 5 for 10MHz at 50% duty cycle

reg [2:0] count; //3 bit counter

initial begin
	clk_div = 1'b0;
	count = 3'd0;
end

always @ (posedge clk or posedge reset) begin

	if(reset == 1'b1) begin
		count <= 3'd0;
		clk_div <= 1'b0;
	end
	else if(count == constantNum) begin //if counter equals constant, invert clock and reset counter
		count <= 3'd0;
		clk_div <= ~clk_div;
	end
	else count <= count + 1'd1; //else add 1
end
endmodule
