`timescale 1ns / 1ps
`include "counter5.v"

module counter5_tb;

reg clock;  //declare registers and variables
reg reset;
reg updown;
reg enable;
wire [4:0] count;



counter5 count5(.clk(clock),.reset(reset),.updown(updown),.enable(enable),.count(count)); //instantiate module to test

initial begin //stuff to do once

	$display("TIME:\t CLK:\t RESET:\t ENABLE:\t UPDOWN:\t COUNTER:");
	$monitor("%g\t %b\t %b\t %b\t  %b\t   %b\t", $time, clock, reset, enable, updown, count);
	clock = 0;
	reset = 1;
	enable = 0;
	updown = 1;
	
	#20 reset = 0;
	#50 enable = 1;
	#610 updown = 0;
	#630 $finish;
end

always begin
	
	#10 clock = ~clock; //every 10 ns invert, 50MHz clock
	
end
endmodule