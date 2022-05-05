// Zak Rowland - November 7th 2018 
// Lab 6 Part 2 - Binary counter

module sync_counter(
input [7:0] D,
input up_down,
input clk,
input reset,
input load,
output reg [7:0] Q
);

always @ (posedge clk) begin

	if(clk == 1'b1) begin
		if(reset == 1'b1) Q <= 8'b00000000; //reset
		else begin
			if(load == 1'b1) Q <= D; //load
			else begin
				if(up_down == 1'b0) begin //up_down == 0 count up
					Q <= Q + 8'b00000001;
				end
				else begin //up_down == 1 count down
					Q <= Q - 8'b00000001;
				end
			end
		end
	end

end
	
endmodule
