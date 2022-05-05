module counter_8bit(

	input clk,
	input reset,
	input start,
	output reg [7:0] count,
	output reg go

);
	
	parameter compare_value = (8'd254); // For <= 
	//parameter compare_value = (8'd254); // For !=
	
	reg [0:0] started;
	
	initial begin
	
		count = 8'd0;
		go = 1'b0;
		started = 1'b0;
	
	end
	
	always @ (posedge clk) begin
	
		if(reset == 1'b1) begin
			
			count <= 8'd0;
			go <= 1'b0;
			started <= 1'b0;
			
		end
		else begin
			
			if(start == 1'b1) started <= 1'b1;
			
			if(started == 1'b1) begin
			
				if(count <= compare_value) begin
			
					count <= count + 8'd1;
					go <= 1'b0;
		
				end
				else begin
				
					count <= 8'd0;
					go <= 1'b1;
					started <= 1'b0;
			
				end
						
			end
			
			else go <= 1'b0;
			
		end
	
	end
	
endmodule