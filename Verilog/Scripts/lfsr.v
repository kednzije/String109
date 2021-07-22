module lfsr(input  [7:0]  seed,
	input  clk,
	input  load,
	output reg [7:0] dout
	);
always @ (posedge clk) begin
	if(load) begin
		dout = seed;
	end
	else begin
		dout = {dout[4] ^ dout[3] ^ dout[1] ^ dout[0], dout[7:1]};
	end
end
endmodule // lfsr