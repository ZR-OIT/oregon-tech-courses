// Zak Rowland - October 11th 2018 
// Structural design for a 2:1 multiplexer using Verilog  
module mux2_1b( 
 	input  a,
	input b,
	input sel,
	output reg x
	);
	
// Structural code for 2:1 multiplexer 	  	
always @ (sel) 
	begin
		case(sel)
			1'b0: x = a;
			1'b1: x = b;
		endcase
	end
endmodule 