// Zak Rowland - October 11th 2018 
// Structural design for a 4bit full adder using Verilog  

module adder_4b(
	input [3:0] a,
	input [3:0] b,
	output[3:0] sum,
	output cout);
	
	wire w1, w2, w3;
	
	fulladder a1(.A(a[0]),.B(b[0]),.Cin(1'b0),.Sum(sum[0]),.Cout(w1));
	fulladder a2(.A(a[1]),.B(b[1]),.Cin(w1),.Sum(sum[1]),.Cout(w2));
	fulladder a3(.A(a[2]),.B(b[2]),.Cin(w2),.Sum(sum[2]),.Cout(w3));
	fulladder a4(.A(a[3]),.B(b[3]),.Cin(w3),.Sum(sum[3]),.Cout(cout));
	
endmodule