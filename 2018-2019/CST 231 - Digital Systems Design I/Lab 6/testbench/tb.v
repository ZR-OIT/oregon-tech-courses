`timescale 1ns / 1ps
module lab6_tb; //No I /O in t e s tbench
reg clk;
reg data_in;
wire [7:0] data_out;
wire parity_led;
wire data_ready;

rx test(.clk(clk), .data_in(data_in), .data_out(data_out), .parity_led(parity_led), .data_ready(data_ready));

initial begin
	$display ("time\t clk data_in data_out parity_led");
 	$monitor ("%g\t %b   %b     %b	   %b", 
	$time, clk, data_in, data_out, parity_led);

   data_in = 1;
clk = 0;
#16 data_in = 0;
#16 data_in = 1;
#16 data_in = 0;
#16 data_in = 0;
#16 data_in = 0;
#16 data_in = 0;
#16 data_in = 1;
#16 data_in = 1;
#16 data_in = 0;
#16 data_in = 1;
#16 data_in = 1;
#16 data_in = 1;
//#64	$finish;
end

always begin

	#1 clk = ~clk;
end

endmodule
