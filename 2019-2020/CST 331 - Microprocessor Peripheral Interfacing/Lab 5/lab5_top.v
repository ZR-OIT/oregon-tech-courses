`timescale 1ns / 1ns
module lab5_top(
	input EBICS0,		 		// CS0 line from EBI
	input EBICS3,		 		// CS3 line from EBI
	input EBIWE,				// WE line from EBI
	input EBIOE,				// OE line from EBI
	input [2:0] ADDR,	 		// EBIA[15:13] address lines
	input [9:0] SW,				// Set of 10 switches on Sidewinder
	output CE2,			 		// Inverted CS0 line
	inout wire [7:0] DATA_BUS,    // Set of 8 lines for data
	output wire [11:0] LED				// Set of 12 LEDs on Sidewinder
);

assign CE2 = ~EBICS0; // Invert CS0 and assign to CE2
assign LED[11:10] = SW[9:8];
assign LED[9:8] = 2'b00;

// Route all required signals for FPGA I/O port
lab5_enable_io_port enable_io(.cs3(EBICS3), .we(EBIWE), .oe(EBIOE), .address(ADDR[2:0]), .switches(SW[7:0]), .data_bus(DATA_BUS[7:0]), .led(LED[7:0]));

endmodule

