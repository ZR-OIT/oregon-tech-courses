// Zak Rowland - October 4th 2018 
// Structural design for a full adder using Verilog  
module fulladder( 
 	input  A, B, Cin,  	
	output Sum, Cout);
	
 	wire S1, T1, T2, T3; 
// Structural code for 1 bit full adder 	  	
	xor 	U1 (S1, A, B); 
 	xor 	U2 (Sum, S1, Cin); 
 	 	 
 	and 	U3 (T3, A, B);  	
	and 	U4 (T2, B, Cin); 
 	and 	U5 (T1, A, Cin); 
 	 	 
 	or  	U6 (Cout, T1, T2, T3);
endmodule 
