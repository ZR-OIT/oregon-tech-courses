// Zak Rowland - October 11th 2018 
// Structural design for a 4bit 2:1 multiplexer using Verilog  
module mux2_4b( 
 	input  [3:0] a,
	input [3:0] b,
	input sel,
	output [3:0] y
	);
	
// Structural code for a 4bit 2:1 multiplexer 	  	
	mux2_1b m1(.a(a[0]),.b(b[0]),.sel(sel),.x(y[0]));
	mux2_1b m2(.a(a[1]),.b(b[1]),.sel(sel),.x(y[1]));
	mux2_1b m3(.a(a[2]),.b(b[2]),.sel(sel),.x(y[2]));
	mux2_1b m4(.a(a[3]),.b(b[3]),.sel(sel),.x(y[3]));
endmodule 