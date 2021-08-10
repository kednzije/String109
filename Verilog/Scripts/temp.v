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
wire [31:0] pcA;
wire [31:0] pcB;
wire [31:0] nxtpc;

wire [31:0] instr;
wire [6:0] op;
wire [2:0] func3;
wire [6:0] func7;

wire [4:0] ra;
wire [4:0] rb;
wire [4:0] rw;
wire [31:0] busW;
wire [31:0] busA;
wire [31:0] busB;

wire [2:0] extop;
wire regwr;
wire ALUAsrc;
wire [1:0] ALUBsrc;
wire [3:0] ALUctr;
wire [2:0] branch;
wire mem2reg;
wire memwr;
wire [2:0] memop;
wire pcAsrc, pcBsrc;

wire [31:0] imm;
wire [31:0] alua;
wire [31:0] alub;
wire less, zero;
wire [31:0] aluresult;

assign instr = imemdataout;
assign op = instr[6:0];
assign func3 = instr[14:12];
assign func7 = instr[31:25];
assign ra = instr[19:15];
assign rb = instr[24:20];
assign rw = instr[11:7];

contrgen __contrgen(op, func3, func7, extop, regwr, ALUAsrc, ALUBsrc, ALUctr, branch, mem2reg, memwr, memop);

immgen __immgen(instr[31:7], extop, imm);

regfile myregfile(~clock, regwr, ra, rb, rw, busW, busA, busB);

mux2 __mux2(busA, pc, alua, ALUAsrc);
mux3 __mux3(busB, imm, 32'b100, alub, ALUBsrc);
alu __alu(alua, alub, ALUctr, less, zero, aluresult);

branchcond __branchcond(branch, zero, less, pcAsrc, pcBsrc);

mux2 __pcAsrcMux(32'b100, imm, pcA, pcAsrc);
mux2 __pcBsrcMux(pc, busA, pcB, pcBsrc);
assign nxtpc = pcA + pcB;
assign imemaddr = nxtpc;
assign imemclk = clock;

assign dmemaddr = aluresult;
assign dmemdatain = busB;
assign dmemop = memop;
assign dmemwe = memwr;
assign dmemrdclk = clock;
assign dmemwrclk = ~clock;
mux2 __regwr(aluresult, dmemdataout, busW, mem2reg);

assign dbgdata = pc;

always @(posedge clock) begin
	if(reset) begin
		pc = 0;
	end else begin
		pc = imemdataout;
	end
end

endmodule

module contrgen (
	input [6:0] op,
	input [2:0] func3,
	input [6:0] func7,
	output wire [2:0] extop,
	output wire regwr,
	output wire ALUAsrc,
	output wire [1:0] ALUBsrc,
	output wire [3:0] ALUctr,
	output wire [2:0] branch,
	output wire mem2reg,
	output wire memwr,
	output wire [2:0] memop
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

module immgen (
	input [24:0] instr_31_7, 
	input [2:0] extop, 
	output wire [31:0] imm
);

wire [31:0] immI;
wire [31:0] immU;
wire [31:0] immS;
wire [31:0] immB;
wire [31:0] immJ;

assign immI = {{20{instr_31_7[24]}}, instr_31_7[24:13]};
assign immU = {instr_31_7[24:5], 12'b0};
assign immS = {{20{instr_31_7[24]}}, instr_31_7[24:18], instr_31_7[4:0]};
assign immB = {{20{instr_31_7[24]}}, instr_31_7[0], instr_31_7[23:18], instr_31_7[4:1], 1'b0};
assign immJ = {{12{instr_31_7[24]}}, instr_31_7[12:5], instr_31_7[13], instr_31_7[23:14], 1'b0};

assign imm = (extop == 3'b000)
				? immI
				: ((extop == 3'b001)
					? immU
					: ((extop == 3'b010)
						? immS
						: ((extop == 3'b011)
							? immB
							: immJ)));

endmodule 

module regfile(
	input wrclk, 
	input regwr, 
	input [4:0] ra, 
	input [4:0] rb, 
	input [4:0] rw, 
	input [31:0] busW, 
	output wire [31:0] busA, 
	output wire [31:0] busB
);
reg [31:0] regs[31:0];

assign busA = regs[ra];
assign busB = regs[rb];

always @(posedge wrclk) begin
	regs[0] = 0;
	if(regwr && rw != 0) begin
		regs[rw] = busW;		
	end
end

endmodule

module mux2(
	input [31:0] input0,
	input [31:0] input1,
	output [31:0] data,
	input selector
);

assign data = selector ? input1 : input0;

endmodule

module mux3(
	input [31:0] input0, 
	input [31:0] input1, 
	input [31:0] input2, 
	output [31:0] data, 
	input [1:0] selector 
);

assign data = selector[1]
				? input2
				: (selector[0] 
					? input1
					: input0);

endmodule

module alu(
	input [31:0] dataa,
	input [31:0] datab,
	input [3:0]  ALUctr,
	output less,
	output zero,
	output [31:0] aluresult);

wire [31:0] res;
wire cf, of, __zero;
reg [31:0] __alures;

adder __adder(dataa, datab, ALUctr == 4'b1000 || ALUctr == 4'b0010 || ALUctr == 4'b1010, res, cf, __zero, of);

assign zero = (~(|aluresult) & ~(ALUctr == 4'b0010 || ALUctr == 4'b1010)) | (__zero & (ALUctr == 4'b0010 || ALUctr == 4'b1010));
assign less = (ALUctr[3] & cf) | ((~ALUctr[3]) & (of != res[31] && __zero == 0));
assign aluresult = __alures;

always @(*) begin
	casex (ALUctr)
		4'bx000: begin
			__alures = res;
		end
		4'bx001: begin
			__alures = dataa << datab[4:0];
		end
		4'bx010: begin
			__alures = less;
		end
		4'bx011: begin
			__alures = datab;
		end
		4'bx100: begin
			__alures = dataa ^ datab;
		end
		4'b0101: begin
			__alures = dataa >> datab[4:0];
		end
		4'b1101: begin
			__alures = dataa >> datab[4:0] | ({32{dataa[31]}} << (32 - datab[4:0]));
		end
		4'bx110: begin
			__alures = dataa | datab;
		end
		4'bx111: begin
			__alures = dataa & datab;
		end
		default:
			__alures = 0;
	endcase
end

endmodule

module adder(
	input  [31:0] A,
	input  [31:0] B,
	input  addsub,
	output [31:0] F,
	output cf,
	output zero,
	output of
	);

wire [31:0] __B;
wire c;

assign __B = {32{addsub}} ^ B;
assign {c, F} = A + __B + addsub;
assign zero = ~(| F);
assign cf = c ^ addsub;
assign of = (A[31] == __B[31]) && (F[31] != A[31]);

endmodule

module branchcond(
	input [2:0] branch, 
	input zero, 
	input less, 
	output wire pcAsrc, 
	output wire pcBsrc
);

assign pcAsrc = (~branch[2] & (branch[1] ^ branch[0])) | (branch[2] & ~branch[1] & (branch[0] ^ zero)) | (branch[2] & branch[1] & (branch[0] ^ less));
assign pcBsrc = ~branch[2] & branch[1] & ~branch[0];

endmodule