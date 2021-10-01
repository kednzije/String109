module BranchCond (
	input 			[2:0] 	branch, 
	input 					zero, 
	input 					less, 
	output 	wire 			pcAsrc, 
	output 	wire 			pcBsrc
);

assign pcAsrc = (~branch[2] & (branch[1] ^ branch[0])) 
				| (branch[2] & ~branch[1] & (branch[0] ^ zero)) 
				| (branch[2] & branch[1] & (branch[0] ^ less));
// assign pcAsrc = (~branch[2]
// 					? (branch[1] ^ branch[0])
// 					: (~branch[1]
// 						? (branch[0] ^ zero)
// 						: (branch[0] ^ less)));
assign pcBsrc = ~branch[2] & branch[1] & ~branch[0];

endmodule //BranchCond