module clkdiv_48MHz_to_9600Hz(
input clk_in,
output reg clk_out
);

//48MHz / 9600Hz = 12500 -> 12500 / 2 = 6250 count
reg [11:0] count; //floor of log(6250)/log(2) + 1

always @ (posedge clk_in) begin
	
	if (count == 12'd2499) begin
		clk_out <= ~clk_out;
		count <= 12'd0;
	end
	else count <= count + 1'b1;
		
end
endmodule	