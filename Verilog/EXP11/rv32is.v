`include "../ImmGen.v"
`include "../ContrGen.v"
`include "../RegFile.v"
`include "../Mux2.v"
`include "../Mux4.v"
`include "../ALU.v"
`include "../BranchCond.v"

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

reg 	[31:0] 	pc;
wire 	[31:0]	pcA, pcB, nxtpc;

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

ImmGen immgen(
	.instr_31_7(instr[31:7]), 
	.extop(extop), 
	.imm(imm)
);

ContrGen contrgen(
	.op(op),
	.func3(func3),
	.func7(func7),
	.extop(extop),
	.regwr(regwr),
	.ALUAsrc(ALUAsrc),
	.ALUBsrc(ALUBsrc),
	.ALUctr(ALUctr),
	.branch(branch),
	.mem2reg(mem2reg),
	.memwr(memwr),
	.memop(memop)
);

RegFile myregfile(
	.wrclk(clock), 
	.regwr(regwr), 
	.ra(ra), 
	.rb(rb), 
	.rw(rw), 
	.busW(busW), 
	.busA(busA), 
	.busB(busB)
);

Mux2 mux2_ALUAsrc(
	.selector(ALUAsrc),
	.input0(busA),
	.input1(pc),
	.data(alua)
);

Mux4 mux4_ALUBsrc(
	.selector(ALUBsrc),
	.input0(busB),
	.input1(imm),
	.input2(32'd4),
	.input3(32'd0),
	.data(alub)
);

ALU alu(
	.dataa(alua),
	.datab(alub),
	.ALUctr(ALUctr),
	.less(less),
	.zero(zero),
	.aluresult(aluresult)
);

BranchCond branchcond(
	.branch(branch & 3'b000), 
	.zero(zero), 
	.less(less), 
	.pcAsrc(pcAsrc),
	.pcBsrc(pcBsrc)
);

Mux2 mux2_pcAsrc(
	.selector(pcAsrc),
	.input0(32'd4),
	.input1(imm),
	.data(pcA)
);

Mux2 mux2_pcBsrc(
	.selector(pcBsrc),
	.input0(pc),
	.input1(busA),
	.data(pcB)
);

assign nxtpc = pcA + pcB;
assign imemaddr = nxtpc;
assign imemclk = ~clock;

assign dmemaddr = aluresult;
assign dmemdatain = busB;
assign dmemop = memop;
assign dmemwe = memwr;
assign dmemrdclk = clock;
assign dmemwrclk = ~clock;
Mux2 mux2_regwr(
	.selector(mem2reg),
	.input0(aluresult),
	.input1(dmemdataout),
	.data(busW)
);

assign dbgdata = pc;

always @(posedge clock) begin
	if(reset) begin
		pc = 0;
	end
	else begin
		pc = nxtpc;
	end
end

endmodule // rv32is