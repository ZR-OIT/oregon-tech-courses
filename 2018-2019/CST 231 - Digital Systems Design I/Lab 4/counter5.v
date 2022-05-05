`timescale 1ns / 1ps

module counter5(
	input clk,
	input reset, //1 = reset (synchronous)
	input updown, //1 = count up
	input enable, //1 = enable
	output reg [4:0] count
);

always @ (posedge clk) begin

	if(reset) count <= 5'b00000;
	else begin
		if(enable) begin
			if(updown) count <= count + 1'b1;
			else count <= count - 1'b1;
		end
	end

end
endmodule