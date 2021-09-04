`include "../Adder.v"
`include "../Shifter.v"

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
