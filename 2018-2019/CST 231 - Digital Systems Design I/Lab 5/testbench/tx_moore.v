// 4-State Moore state machine

// A Moore machine's outputs are dependent only on the current state.
// The output is written only when the state changes.  (State
// transitions are synchronous.)

module tx_moore
(
	input	clk,
	input go,
	input [7:0] data,
	output reg data_out,
	output reg [1:0] state_out
);
	
	// Declare state register
	//reg		[1:0] state;
	reg		[3:0] count;
	
	// Declare states
	parameter START = 2'd0, SHIFT = 2'd1, STOP1 = 2'd2, STOP2 = 2'd3;
	
	initial begin
		state_out = 2'd0;
		count = 4'd0;
	end
	
	// Output depends only on the state
	always @ (state_out) begin
		case (state_out)
			START:
				if(go) data_out = 1'b1;
				else data_out = 1'b0;
			SHIFT:
				data_out = data[count];
			STOP1:
				data_out = 1'b1;
			STOP2:
				data_out = 1'b1;
			default:
				data_out = 1'b0;
		endcase
	end
	
	// Determine the next state
	always @ (posedge clk) begin
		case (state_out)
				START:
					if(go) state_out <= SHIFT;
					else state_out <= START;
				SHIFT:
					if (count < 4'd8) begin
						count <= count + 1'd1;
						state_out <= SHIFT;
					end
					else begin
						count <= 4'd0;
						state_out <= STOP1;
					end
				STOP1:
					state_out <= STOP2;
				STOP2:
					state_out <= START;
				default:
					state_out <= START;
			endcase
	end
	
endmodule
