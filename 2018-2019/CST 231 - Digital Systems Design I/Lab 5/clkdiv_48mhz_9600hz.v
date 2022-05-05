module clkdiv_48mhz_9600hz(
input clk_in,
output clk_out
);

reg [11:0] count; //log(2500)/log(2) + 1

always @ (posedge clk_in) begin
	if (count == 11'd2499) begin
	clk_out = ~clk_out;
	count = 11'd0;
	end
	else count = count + 1'b1;
end
end module	