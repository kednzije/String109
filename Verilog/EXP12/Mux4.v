module Mux4 (
	input 	[1:0]	selector,
	input 	[31:0]	input0,
	input 	[31:0]	input1,
	input 	[31:0]	input2,
	input 	[31:0]	input3,
	output 	[31:0]	data
);

assign data = (selector[1] == 0)
				? (selector[0] == 0 ? input0 : input1)
				: (selector[0] == 0 ? input2 : input3);

endmodule //Mux4