`timescale 1ns / 1ns
module lab5_testbench;
	reg EBICS3;		 		// CS3 line from EBI
	reg EBIWE;				// WE line from EBI
	reg EBIOE;				// OE line from EBI
	reg [2:0] ADDR;		 		// EBIA[15:13] address lines
	reg [9:0] SW;				// Set of 10 switches on Sidewinder
	wire [7:0] DATA_BUS;   		        // Set of 8 lines for data
	wire [7:0] LED;				// Set of 8 LEDs on Sidewinder


	// Route all required signals for FPGA I/O port
	lab5_enable_io_port enable_io(.cs3(EBICS3), .we(EBIWE), .oe(EBIOE), .address(ADDR[2:0]), .switches(SW[7:0]), .data_bus(DATA_BUS[7:0]), .led(LED[7:0]));

	reg [7:0] data_reg; // Register of data to manipulate the bus
	assign DATA_BUS = data_reg; // Assign data bus to data register

	initial begin

		EBICS3 = 1'b1; // CS3 isn't asserted
		EBIWE = 1'b1; // WE isn't asserted
		EBIOE = 1'b1; // OE isn't isserted
		ADDR = 3'b000; // Address isn't in range
		SW = 10'b0000000000; // Switches are off
		data_reg = 8'bzzzzzzzz; // Data bus is low impedance
		
		// Lowest settings (EBI) write cycle
		// tEBI-AS = 1 cycle
		// tEBI-WP = 1 cycle 
		// tEBI-WR = 1 cycle
		# 80 EBICS3 = 1'b0; // Assert CS3 after 4 cycles
		# 20 EBIWE = 1'b0 ; // Assert WE after 1 cycle
		# 0  data_reg = 8'b10010110; // Drive the data bus with a value
		# 20 EBIWE = 1'b1; // Don't assert WE after 1 cycle
		# 20 EBICS3 = 1'b1; // Don't assert CS3 after 1 cycle
		# 0  data_reg = 8'bzzzzzzzz; // Stop driving data bus
		# 20 SW = 10'b1010101110; // Give the switches a value after 1 cycle
		
		// Low settings (EBI) write cycle, address in range
		// tEBI-AS = 1 cycle
		// tEBI-WP = 2 cycle
		// tEBI-WR = 1 cycle
		# 40 EBICS3 = 1'b0; // Assert CS3 after 2 cycles
		# 0  ADDR[2:0] = 3'b001; // Access address in range
		# 20 EBIWE = 1'b0; // Assert WE after 1 cycle
		# 0  data_reg = 8'b10010110; // Drive the data bus with a value
		# 40 EBIWE = 1'b1; // Don't assert WE after 2 cycles
		# 20 EBICS3 = 1'b1; // Don't assert CS3 after 1 cycle
		# 0  data_reg = 8'bzzzzzzzz; // Stop driving data bus
		# 20 SW = 10'b0011110000; // Give the switches a value after 1 cycle
		# 0  ADDR = 3'b000; // Access address out of range
		
		// Lowest settings (EBI) read cycle
		// tEBI-RC = 2 cycles
		# 40 EBICS3 = 1'b0; // Assert CS3 after 2 cycles
		# 0  EBIOE = 1'b0 ; // Assert OE
		# 40 EBICS3 = 1'b1; // Don't assert CS3 after 2 cycles
		# 0  EBIOE = 1'b1; // Don't assert OE
		
		// Lowest settings (EBI) read cycle, address in range
		// tEBI-RC = 2 cycles
		# 0  ADDR = 3'b001; // Access address in range
		# 40 EBICS3 = 1'b0; // Assert CS3 after 2 cycles
		# 0  EBIOE = 1'b0 ; // Assert OE
		# 40 EBICS3 = 1'b1; // Don't assert CS3 after 2 cycles
		# 0  EBIOE = 1'b1; // Don't assert OE
		
		// Low settings (EBI) write cycle, address in range, no CS3
		// tEBI-AS = 1 cycle
		// tEBI-WP = 2 cycle
		// tEBI-WR = 1 cycle
		//# 40 EBICS3 = 1'b0; // Assert CS3 after 2 cycles
		# 40  ADDR[2:0] = 3'b001; // Access address in range
		# 20 EBIWE = 1'b0; // Assert WE after 1 cycle
		# 0  data_reg = 8'b01011111; // Drive the data bus with a value
		# 40 EBIWE = 1'b1; // Don't assert WE after 2 cycles
		# 20 EBICS3 = 1'b1; // Don't assert CS3 after 1 cycle
		# 0  data_reg = 8'bzzzzzzzz; // Stop driving data bus
		# 20 SW = 10'b0011110000; // Give the switches a value after 1 cycle
		# 0  ADDR = 3'b000; // Access address out of range
		
		// Low settings (EBI) write cycle, address in range
		// tEBI-AS = 1 cycle
		// tEBI-WP = 2 cycle
		// tEBI-WR = 1 cycle
		# 40 EBICS3 = 1'b0; // Assert CS3 after 2 cycles
		# 0  ADDR[2:0] = 3'b001; // Access address in range
		# 20 EBIWE = 1'b0; // Assert WE after 1 cycle
		# 0  data_reg = 8'b01011111; // Drive the data bus with a value
		# 40 EBIWE = 1'b1; // Don't assert WE after 2 cycles
		# 20 EBICS3 = 1'b1; // Don't assert CS3 after 1 cycle
		# 0  data_reg = 8'bzzzzzzzz; // Stop driving data bus
		# 20 SW = 10'b0000001111; // Give the switches a value after 1 cycle
		# 0  ADDR = 3'b000; // Access address out of range
		
		# 40 $stop; // Stop
	
	end

	endmodule

