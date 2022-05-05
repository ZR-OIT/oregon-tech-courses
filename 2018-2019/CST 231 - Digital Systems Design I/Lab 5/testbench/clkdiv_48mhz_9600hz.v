`timescale 1ns / 1ps

module clkdiv_48mhz_9600hz( //actually 50MHz to 9600Hz due to test benching
	input clk_in,
	input reset,
	output reg clk_out,
	output reg [11:0] count //log(2604)/log(2) + 1
);

parameter constantNum = 12'd2604; //count to 2604 for ~9600MHz from 50Mhz

initial begin
	clk_out = 1'b0;
	count = 12'd0;
end

always @ (posedge clk_in or posedge reset) begin
	
	if(reset == 1'b1) begin
		count <= 12'd0;
		clk_out <= 1'b0;
	end
	else if (count == constantNum) begin
		clk_out <= ~clk_out;
		count <= 12'd0;
	end
	else count <= count + 1'd1;
end
endmodule