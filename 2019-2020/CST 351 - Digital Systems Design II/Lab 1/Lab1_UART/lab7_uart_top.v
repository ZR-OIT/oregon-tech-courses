module lab1_uart_top(
	input CLOCK_50,
	input [4:0] SW,
	output DATA_OUT
);

wire clk_div_9600Hz/*synthesis keep*/; //9600Hz clock wire
wire go_tx/*synthesis keep*/;
wire [7:0] tx_char/*synthesis keep*/;
wire [4:0] switch_data/*synthesis keep*/;

assign switch_data[4:0] = SW[4:0];

clkdiv_50MHz_to_9600Hz clock_9600Hz(.clk_in(CLOCK_50), .clk_out(clk_div_9600Hz));
tx_decoder transmitter_decoder(.clk(clk_div_9600Hz), .data(switch_data), .go(go_tx), .tx_character(tx_char));
tx_message transmit_message(.clk(clk_div_9600Hz), .datain(tx_char), .go(go_tx), .dataout(DATA_OUT));

endmodule