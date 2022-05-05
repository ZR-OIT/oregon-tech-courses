// Zak Rowland - November 7th 2018 
// Lab 6 Part 1 - Synchronous Shift Register

module shift_reg(
	input [3:0] D,
	input sin,
	input load,
	input l_r,
	input clk,
	input reset,
	output reg [3:0] Q,
	output reg sout
	);
	
	always @ (posedge clk or posedge reset) begin
		if(reset == 1'b1) begin //if reset is 1, clear shift register
			Q <= 4'b0000;
			sout <= 1'b0;
		end
		else begin
			if(clk == 1'b1) begin
				if(load == 1'b0) begin //load == 0
					if(l_r == 1'b0) begin //l_r == 0 shift right
						sout <= Q[0];
						Q[2:0] <= Q[3:1];
						Q[3] <= sin;
					end
					else begin //l_r == 1 shift left
						sout <= Q[3];
						Q[3:1] <= Q[2:0];
						Q[0] <= sin;
					end
				end
				else Q <= D; //load == 1
			end
		end
	end
	
endmodule