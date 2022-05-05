module threeInputAnd(
	input CLOCK_50,
	input [2:0] SW,
	output reg [0:0] LEDR
);

	wire ab, abc /*synthesis keep*/;
	
	assign ab = SW[0] & SW[1];
	assign abc = ab & SW[2];
	
	always @ (posedge CLOCK_50) begin
		LEDR[0] <= abc;
	end
	
endmodule