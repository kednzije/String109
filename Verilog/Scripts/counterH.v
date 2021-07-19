
module counterH(
	input  clk,
	input  en,
	input  rst,
	input  [5:0] cnt_limit,
	output reg [5:0] Q,
	output reg rco
	);

always @ (posedge clk) begin
	if(en) begin
		if(rst) begin
			Q = 6'b0000;
			rco = 1;
		end
		else begin
			if(Q == cnt_limit - 1) begin
				Q = 0;
				rco = 1;
			end
			else begin
				Q = Q + 1;
				rco = 0;
			end
		end
	end
end

endmodule // counterH