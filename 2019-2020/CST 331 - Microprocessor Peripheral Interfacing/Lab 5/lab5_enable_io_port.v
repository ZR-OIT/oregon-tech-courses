`timescale 1ns / 1ns
module lab5_enable_io_port(
	input cs3, // CS3 line from EBI
	input we, // WE line from EBI
	input oe, // OE line from EBI
	input [2:0] address, // EBIA[15:13] address lines
	input [7:0] switches, // Switches on Sidewinder
	inout [7:0] data_bus, // Set of 8 lines for data
	output reg [7:0] led // LEDs on Sidewinder
);

// If CS is asserted, OE is asserted, WE isn't asserted, and EBIA[15:13] == 3b'001 
//		then drive data bus with Sidewinder switch data
// Else drive data bus low impedence
assign data_bus = (~cs3 & ~oe & we & ~address[2] & ~address[1] & address[0]) ? switches[7:0] : 8'bzzzzzzzz;

// If CS is asserted, WE is asserted, OE isn't asserted, and EBIA[15:13] == 3'b0XX then trigger 
always @ (negedge (~cs3 & ~we  & oe & ~address[2])) begin
if(~address[1] & address[0]) // If EBIA[15:13] == 3'b001
	led[7:0] = data_bus[7:0]; // Assign data on bus to LEDs
else
	led[7:0] = led[7:0] ^ data_bus[7:0]; // Assign inverted data to LEDs
end
endmodule