// Zak Rowland - 11/20/2018
// Lab 7 - Stoplight State Machine

// A Moore machine's outputs are dependent only on the current state.
// The output is written only when the state changes.  (State
// transitions are synchronous.)

module stoplight_moore_mac
(
	input	clk, 
	input sensor,
	input reset,
	output reg [2:0] HWY_color, 
	output reg [2:0] FARM_color //Colors are RGB - e.g. Red FARM_color = 100 
);
	
	// Declare state register
	reg [4:0] state;
	
	// Declare count register
	reg [3:0] count;
	
	// Declare states
	parameter RESET = 5'b10000, HWY_G = 5'b01000, HWY_Y = 5'b00100, FARM_G = 5'b00010, FARM_Y = 5'b00001;
	
	// Output depends only on the state
	always @ (state) begin
		case (state)
			RESET:
				begin
				HWY_color = 3'b100;
				FARM_color = 3'b100;
				end
			HWY_G:
				begin
				HWY_color = 3'b010;
				FARM_color = 3'b100;
				end
			HWY_Y:
				begin
				HWY_color = 3'b110;
				FARM_color = 3'b100;
				end
			FARM_G:
				begin
				HWY_color = 3'b100;
				FARM_color = 3'b010;
				end
			FARM_Y:
				begin
				HWY_color = 3'b100;
				FARM_color = 3'b110;
				end
		endcase
	end
	
	// Determine the next state
	always @ (posedge clk or posedge reset) begin
		if (reset == 1'b1) begin
			count <= 4'b0000;
			state <= RESET;
		end
		else begin
			case (state)
				RESET:
					if(count != 4'b0101) begin
						count <= count + 4'b0001;
						state <= RESET;
					end
					else begin
						count <= 4'b0000;
						state <= HWY_G;
					end
				HWY_G:
					if (sensor == 1'b1) begin
						count <= 4'b0000;
						state <= HWY_Y;
					end
				HWY_Y:
					if (count != 4'b1010) begin
						count <= count + 4'b0001;
						state <= HWY_Y;
					end
					else begin
						count <= 4'b0000;
						state <= FARM_G;
					end
				FARM_G:
					if (count != 4'b1111) begin
						count <= count + 4'b0001;
						state <= FARM_G;
					end
					else begin
						count <= 4'b0000;
						state <= FARM_Y;
					end
				FARM_Y:
					if (count != 4'b1010) begin
						count <= count + 4'b0001;
						state <= FARM_Y;
					end
					else begin
						count <= 4'b0000;
						state <= HWY_G;
					end
			endcase
		end
	end
	
endmodule
