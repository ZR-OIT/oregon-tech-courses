`timescale 1ns / 1ps
`include "clkdiv_48mhz_9600hz.v"
//`include "tx.v"
`include "tx_moore.v"

module lab5_tb;

reg clk;
reg go_switch;
reg reset;
wire data_out;
wire clk_div9600hz;
wire [11:0] counter;
wire [1:0] state;
reg [7:0] test_data;

clkdiv_48mhz_9600hz clk_9600hz(.clk_in(clk),.reset(reset),.clk_out(clk_div9600hz),.count(counter));
//tx output_test(.clk(clk_div9600hz),.go(go_switch),.data(test_data),.dataout(data_out));
tx_moore output_test(.clk(clk_div9600hz),.go(go_switch),.data(test_data),.data_out(data_out),.state_out(state));

initial begin //do once

	//$display("TIME:\t SRC_CLK:\t 9600CLK:\t GO_SW:\t DATA_OUT:\t");
	//$monitor("%g\t %b\t   %b\t     %b\t     %b\t", $time, clk, clk_div9600hz, go_switch, data_out);
	
	$display("TIME:\t GO:\t STATE:\t DATA_OUT:\t");
	$monitor("%g\t %b\t %d\t %b\t", $time, go_switch, state, data_out);
	
	//$monitor("%g\t %b\t", $time, clk_div9600hz);
	
	
	clk = 0;
	go_switch = 0;
	test_data = 8'b01010101; //define data to send here
	
	#20 reset = 1;
	
	#20 reset = 0;
	
	#52080 go_switch = 1;
	#1000 go_switch = 0;
	
	#100000000 $stop;

end

always begin

	#10 clk = ~clk; //every 10ns invert clk, 50MHz

end

endmodule