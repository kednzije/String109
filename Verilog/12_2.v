module rv32is(
	input 	clock,
	input 	reset,
	output [31:0] imemaddr,
	input  [31:0] imemdataout,
	output 	imemclk,
	output [31:0] dmemaddr,
	input  [31:0] dmemdataout,
	output [31:0] dmemdatain,
	output 	dmemrdclk,
	output	dmemwrclk,
	output [2:0] dmemop,
	output	dmemwe,
	output [31:0] dbgdata);

reg [31:0] pc;
wire [2:0] extop;

assign dbgdata = pc;

always @(posedge clock) begin
	if(reset) begin
		pc = 0;
	end else begin
		
	end
end

endmodule

module contrgen (
	input [6:0] op;
	input [2:0] func3;
	input [6:0] func7;
	output wire [2:0] extop;
	output wire regwr;
	output wire ALUAsrc;
	output wire [1:0] ALUBsrc;
	output wire [3:0] ALUctr;
	output wire [2:0] branch;
	output wire mem2reg;
	output wire memwr;
	output wire [2:0] memop;
);

assign extop[2] = (&op[6:5]) & ~op[4] & (&op[3:2]);
assign extop[1] = op[5] & (&(~op[4:2]));
assign extop[0] = (~op[6] & op[4] & ~op[3] & op[2]) | ((&op[6:5]) & (&(~op[4:2])));

assign regwr = op[5] & (&(~op[4:2]));

assign ALUAsrc = (~op[6] & ~op[5] & op[4] & ~op[3] & op[2]) | (op[6] & op[5] & ~op[4] & op[2]);

assign ALUBsrc[1] = op[6] & op[5] & ~op[4] & op[2];
assign ALUBsrc[0] = (~op[6] & (~op[5] | ~op[4]) & ~op[3] & ~op[2]) | (~op[6] & op[4] & ~op[3] & op[2]);

assign ALUctr = (op[4] & ~op[3] & op[2])
					? (op[5] ? 4'b0011 : 4'b0000)
					: ((~op[6] & ~op[5] & op[4] & ~op[3] & ~op[2])	
						? ((&func3[2:0])
							? 4'b0000
							: ((~func3[2] & func3[1])
								? {func3[0], 3'b010}
								: {func7[5], func3[2:0]}))
						: ((~op[6] & op[5] & op[4] & ~op[3] & ~op[2])
							? ((~func3[2] & func3[1])
								? {func3[0], 3'b010}
								: {func7[5], func3[2:0]})
							: ((&op[6:5])
								? (op[2]
									? 4'b0000
									: {&func3[2:1], 3'b010})
								: 4'b0000)));						

assign branch[2] = op[6] & op[5] & (&(~op[4:2]));
assign branch[1] = op[6] & op[5] & ((~op[3] & op[2]) | ((&(~op[4:2])) & func3[2]));
assign branch[0] = op[6] & op[5] & (op[3] | func3[0]);

assign mem2reg = &(~op[6:2]);

assign memwr = ~op[6] & op[5] & ~op[4] & ~op[3] & ~op[2];

assign memop = func3[2:0];

endmodule