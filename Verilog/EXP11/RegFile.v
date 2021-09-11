module RegFile (
	input 					wrclk, 
	input 					regwr, 
	input 			[4:0] 	ra, 
	input 			[4:0] 	rb, 
	input 			[4:0] 	rw, 
	input 			[31:0] 	busW, 
	output 	wire 	[31:0] 	busA, 
	output 	wire 	[31:0] 	busB
);

reg [31:0] regs[31:0];

initial begin
	regs[0] = 0;
end

assign busA = regs[ra];
assign busB = regs[rb];

always @(posedge wrclk) begin
	regs[0] <= 0;
	if(regwr && rw != 0) begin
		regs[rw] <= busW;		
	end
end

endmodule //RegFile