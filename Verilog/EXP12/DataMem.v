module DataMem (
	input 			rd_clk,
	input 			wr_clk,
	input  	[2:0]	memop,
	input 			we,
	input 	[31:0] 	wr_addr,
	input 	[31:0] 	datain,
	input 	[31:0] 	rd_addr,
	output 	[31:0] 	dataout
);

/* TODO: Use IP Core to implement the DataMem for data memory. */

endmodule //DataMem