// Zak Rowland - November 8th 2018 
// Lab 6 Part 3 - BCD Counter

module bcd_counter(
input up_down,
input cen,
input clk,
input reset,
output reg [3:0] Q
);

always @ (posedge clk or posedge reset) begin

	if(reset) Q <= 4'b0000;
	else begin
		if(cen == 1'b0) begin //enable active low
			if(up_down == 1'b1)begin //count up
				if(Q > 9) Q <= Q + 4'b0110;
				else Q <= Q + 4'b0001;
			end
			else begin
				if (Q > 9) Q <= Q - 4'b0110;
				else Q <= Q - 4'b0001;
			end
		end
	end

end
endmodule
