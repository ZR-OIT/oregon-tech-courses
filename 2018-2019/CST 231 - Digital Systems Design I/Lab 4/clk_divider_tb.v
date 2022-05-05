`timescale 1ns / 1ps
`include "clk_divider_to_10MHz_20duty.v"
`include "clk_divider_to_10MHz.v"

module clk_divider_tb;

reg clock; //declare registers and variables
reg reset;
wire clk_div10MHz20duty;
wire clk_div10MHz;

clk_divider_to_10MHz_20duty clk10MHz20duty(.clk(clock),.reset(reset),.clk_div(clk_div10MHz20duty));
clk_divider_to_10MHz clk10MHz(.clk(clock),.reset(reset),.clk_div(clk_div10MHz));

initial begin //stuff to do once

	$display("TIME:\t SOURCE:\t RESET:\t 10MHz 20d:\t 10MHz:");
	$monitor("%g\t %b\t %b\t %b\t %b\t", $time, clock, reset, clk_div10MHz20duty, clk_div10MHz);
	
	clock = 0;
	reset = 1;
	
	#20 reset = 0;
	#2500 $finish;

end

always begin

	#5 clock = ~clock; //every 5 ns invert, 100MHz clock

end
endmodule