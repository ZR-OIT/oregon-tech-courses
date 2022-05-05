module counter_32bit(

	input clk,
	input reset,
	output reg [31:0] count,
	output reg go

);
	
	parameter compare_value = (32'hFFFFFFEF); // For <=
	//parameter compare_value = (32'hFFFFFF00); // For !=
	
	always @ (posedge clk) begin
	
		if(reset == 1'b1) begin
			
			count <= 32'd0;
			go <= 1'b0;
			
		end
		else begin
	
			if(count <= compare_value) begin
			
				count <= count + 32'd1;
				go <= 1'b0;
		
			
			end
			else begin
				
				count <= 32'd0;
				go <= 1'b1;
			
			end
			
		end
	
	end
	
endmodule