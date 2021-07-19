module counter(
	input  clk,
	input  en,
	input  rstn,
	input  [3:0] cnt_limit,
	output reg [3:0] Q,
	output reg rco
	);

always @ (posedge clk or negedge rstn) begin
	if(!rstn) begin
		Q = 4'b0000;
		rco = 0;
	end
	else if(clk) begin
		if(en) begin
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

endmodule // counter
