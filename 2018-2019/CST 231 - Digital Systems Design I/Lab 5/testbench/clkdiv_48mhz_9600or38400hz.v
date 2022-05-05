module clkdiv_48mhz_9600or38400hz(
input clk_in,
input button,
output reg led,
output reg clk_out
);
reg sw;
reg [11:0] count; //log(6250)/log(2) + 1

always @ (posedge clk_in) begin
	if (button)  led <= button;
	else  led <= button;
	
		case (button)
		1'b0: begin 
			if (count == 12'd2499) begin
				clk_out <= ~clk_out;
				count <= 12'd0;
			end
		else count <= count + 1'b1;
		end
		1'b1: begin
			if (count == 12'd624) begin
				clk_out <= ~clk_out;
				count <= 12'd0;
			end
			else count <= count + 1'b1;
			end
endcase
end
endmodule	