module Mux2 (
	input 			selector,
	input 	[31:0] 	input0,
	input 	[31:0] 	input1,
	output 	[31:0] 	data
);

assign data = (selector == 0 ? input0 : input1);

endmodule //Mux2