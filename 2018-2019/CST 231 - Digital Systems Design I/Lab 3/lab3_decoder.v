// Original:
// Zak Rowland - November 8th 2018 
// Lab 6 Part 3 - BCD Decoder

// Edited:
// Zak Rowland - January 24th, 2019
// Lab 3 - Seven Segment Display

module lab3_decoder(
input [3:0] bin_in,
output reg [7:0] sseg_out
);

always @ (bin_in) begin

	case(bin_in)
		
		4'b0000: sseg_out = 8'b11000000; //0
		4'b0001: sseg_out = 8'b11111001; //1
		4'b0010: sseg_out = 8'b10100100; //2
		4'b0011: sseg_out = 8'b10110000; //3
		4'b0100: sseg_out = 8'b10011001; //4
		4'b0101: sseg_out = 8'b10010010; //5
		4'b0110: sseg_out = 8'b10000010; //6
		4'b0111: sseg_out = 8'b11111000; //7
		4'b1000: sseg_out = 8'b10000000; //8
		4'b1001: sseg_out = 8'b10010000; //9
		4'b1010: sseg_out = 8'b10001000; //10 - A
		4'b1011: sseg_out = 8'b10000011; //11 - B
		4'b1100: sseg_out = 8'b11000110; //12 - C
		4'b1101: sseg_out = 8'b10100001; //13 - D
		4'b1110: sseg_out = 8'b10000110; //14 - E
		4'b1111: sseg_out = 8'b10001110; //15 - F
		
	endcase
	
end
endmodule