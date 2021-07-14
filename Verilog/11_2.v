module alu(
	input [31:0] dataa,
	input [31:0] datab,
	input [3:0]  ALUctr,
	output less,
	output zero,
	output reg [31:0] aluresult);

reg [31:0] res;
reg addsub, cf, of, __zero;

adder __adder(dataa, datab, ALUctr == 4'b1000 || ALUctr == 4'b0010 || ALUctr == 4'b1010, res, cf, __zero, of);

assign zero = (~(|aluresult) & ~(ALUctr == 4'b0010 || ALUctr == 4'b1010)) | (__zero & (ALUctr == 4'b0010 || ALUctr == 4'b1010));
assign less = (ALUctr[3] & cf) | ((~ALUctr[3]) & (of != res[31] && __zero == 0));

always @(*) begin
	casex (ALUctr)
		4'bx000: begin
			aluresult = res;
		end
		4'bx001: begin
			aluresult = dataa << datab[4:0];
		end
		4'bx010: begin
			aluresult = less;
		end
		4'bx011: begin
			aluresult = datab;
		end
		4'bx100: begin
			aluresult = dataa ^ datab;
		end
		4'b0101: begin
			aluresult = dataa >> datab[4:0];
		end
		4'b1101: begin
			aluresult = dataa >> datab[4:0] | ({32{dataa[31]}} << (32 - datab[4:0]));
		end
		4'bx110: begin
			aluresult = dataa | datab;
		end
		4'bx111: begin
			aluresult = dataa & datab;
		end
		default:
			aluresult = 0;
	endcase
end

endmodule

module adder(
	input  [31:0] A,
	input  [31:0] B,
	input  addsub,
	output reg [31:0] F,
	output reg cf,
	output reg zero,
	output reg of
	);

reg [31:0] __B;
reg c;

always @ (*) begin
	__B = {32{addsub}} ^ B;

	{c, F} = A + __B + addsub;
	zero = ~(| F);
	cf = c ^ addsub;
	of = (A[31] == __B[31]) && (F[31] != A[31]);
end

endmodule