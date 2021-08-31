module ALU (
	input 		[31:0] 	dataa,
	input 		[31:0] 	datab,
	input 		[3:0]  	ALUctr,
	output 	reg			less,
	output 	reg			zero,
	output 	reg	[31:0] 	aluresult
);

wire [31:0] result_tmp[1:0];
wire CF, OF, ZF, SF;
Adder adder(
	.dataa(dataa),
	.datab(datab),
	.add_or_sub(ALUctr[1] | ALUctr[3]), // Add: 0000; Sub: 1000, 0010, 1010
	.result(result_tmp[0]),
	.CF(CF),
	.OF(OF),
	.ZF(ZF),
	.SF(SF)
);
Shifter shifter(
	.dataa(dataa),
	.datab(datab),
	.l_or_r(ALUctr[2]), // Left: x001; Right: 0101, 1101
	.a_or_h(ALUctr[3]), // Arithmetic: 0101; Logical: 1101
	.result(result_tmp[1])
);

always @(*) begin
	casex (ALUctr)
		4'bx00x: begin
			aluresult = result_tmp[ALUctr[0]];
			zero = |aluresult;
			less = 1'b0;
		end
		4'b0010: begin
			zero = ZF;
			less = SF ^ OF;
			aluresult = less;
		end
		4'b1010: begin
			zero = ZF;
			less = CF;
			aluresult = less;
		end
		4'bx011: begin
			aluresult = datab;
			zero = |aluresult;
			less = 1'b0;
		end
		4'bx100: begin
			aluresult = dataa ^ datab;
			zero = |aluresult;
			less = 1'b0;
		end
		4'bx101: begin
			aluresult = result_tmp[ALUctr[0]];
			zero = |aluresult;
			less = 1'b0;
		end
		4'bx110: begin
			aluresult = dataa | datab;
			zero = |aluresult;
			less = 1'b0;
		end
		4'bx111: begin
			aluresult = dataa & datab;
			zero = |aluresult;
			less = 1'b0;
		end
		default: begin
			aluresult = 32'bx;
			zero = 1'bx;
			less = 1'bx;
		end
	endcase
end

endmodule //ALU

module Adder (
	input 			[31:0]	dataa,
	input 			[31:0] 	datab,
	input 					add_or_sub,
	output 	reg 	[31:0] 	result,
	output 	reg 			CF,
	output 	reg 			OF,
	output 	reg 			ZF,
	output 	reg 			SF
);

reg [31:0] datab_xor, result_tmp;
reg carry_n, carry_n_1;

always @(*) begin
	datab_xor = {32{add_or_sub}} ^ datab;

	{carry_n, result} = dataa[31:0] + datab[31:0] + add_or_sub;
	{carry_n_1, result_tmp} = dataa[30:0] + datab[30:0] + add_or_sub;

	CF = carry_n ^ add_or_sub;
	OF = carry_n ^ carry_n_1;
	ZF = ~(|result);
	SF = result[31];
end

endmodule //Adder

module Shifter (
	input 			[31:0]	dataa,
	input 			[31:0] 	datab,
	input 					l_or_r,
	input 					a_or_h,
	output 	reg 	[31:0] 	result
);

always @(*) begin
	casex ({a_or_h, l_or_r})
		2'bx0: begin
			result = dataa << datab[4:0];
		end
		2'b01: begin
			result = dataa >>> datab[4:0];
		end
		2'b11: begin
			result = dataa >> datab[4:0];
		end
		default: begin
			result = 32'bx;
		end	
	endcase
end

endmodule //Shifter