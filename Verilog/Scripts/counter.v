module counter(
	input  clk,
	input  en,
	input  rst,
	input  [3:0] cnt_limit,
	output reg [3:0] Q,
	output reg rco
	);

always @ (posedge clk) begin
	if(en) begin
		if(rst) begin
			Q = 4'b0000;
		end
		else begin
			Q = Q + 1;
			if(Q >= cnt_limit) begin
				Q = 0;
				rco = 1;
			end
			else begin
				rco = 0;
			end
		end
	end
end

endmodule // counter