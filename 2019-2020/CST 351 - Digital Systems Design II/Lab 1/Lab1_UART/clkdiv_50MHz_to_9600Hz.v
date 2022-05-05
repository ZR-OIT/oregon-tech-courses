module clkdiv_50MHz_to_9600Hz(
input clk_in,
output reg clk_out
);

//50MHz / 9600Hz = 5,208.33 -> 5,208 / 2 = 2,604 count
reg [11:0] count; //floor of log(2,604)/log(2) + 1 = 12

always @ (posedge clk_in) begin
	
	if (count == 12'd2604) begin
		clk_out <= ~clk_out;
		count <= 12'd0;
	end
	else count <= count + 12'd1;
		
end
endmodule	