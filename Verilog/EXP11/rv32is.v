module rv32is(
	input 			clock,
	input 			reset,
	output 	[31:0] 	imemaddr,
	input  	[31:0] 	imemdataout,
	output 			imemclk,
	output 	[31:0] 	dmemaddr,
	input  	[31:0] 	dmemdataout,
	output 	[31:0] 	dmemdatain,
	output 			dmemrdclk,
	output			dmemwrclk,
	output 	[2:0]	dmemop,
	output			dmemwe,
	output 	[31:0] 	dbgdata
);

reg 	[31:0] 	pc, pcA, pcB, nxtpc;

wire 	[31:0] 	instr;
wire 	[6:0] 	op;
wire 	[2:0] 	func3;
wire 	[6:0] 	func7;

wire 	[4:0] 	ra, rb, rw;
wire 	[31:0] 	busW, busA, busB;

wire 	[2:0] 	extop;
wire 			regwr;
wire 			ALUAsrc;
wire 	[1:0] 	ALUBsrc;
wire 	[3:0] 	ALUctr;
wire 	[2:0] 	branch;
wire 			mem2reg;
wire 			memwr;
wire 	[2:0] 	memop;
wire 			pcAsrc, pcBsrc;

wire 	[31:0] 	imm;
wire 	[31:0] 	alua, alub, aluresult;
wire 			less, zero;

assign instr = imemdataout;
assign op = instr[6:0];
assign func3 = instr[14:12];
assign func7 = instr[31:25];
assign ra = instr[19:15];
assign rb = instr[24:20];
assign rw = instr[11:7];

ContrGen contrgen(
	
);

endmodule // rv32is