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

reg [31:0] datab_xor, datab_xor_tmp;
reg carry_n, carry_n_1;

always @(*) begin
	// datab_xor = ({32{add_or_sub}} ^ datab[31:0]) + add_or_sub;
	datab_xor = {32{add_or_sub}} ^ datab[31:0];
	datab_xor_tmp = {32{add_or_sub}} ^ datab[31:0] + add_or_sub;

	{carry_n, result} = dataa[31:0] + datab_xor[31:0] + add_or_sub;
	// {carry_n_1, result_tmp} = dataa[30:0] + datab_xor[30:0];

	CF = carry_n ^ add_or_sub;
	// OF = carry_n ^ carry_n_1;
	// OF = (dataa[31] & datab[31]) ^ result[31];
	OF = (dataa[31] == datab_xor_tmp[31]) && (dataa[31] != result[31]);
	ZF = ~(|result[31:0]);
	SF = result[31];
end

endmodule //Adder