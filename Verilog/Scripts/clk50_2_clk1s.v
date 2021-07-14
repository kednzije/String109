module clk50_2_clk1s (
	input clk50,
	output reg clk1s
);

reg [31:0] cnt_clk;

initial begin
	cnt_clk = 0;
	clk1s = 0;
end

always @(posedge clk50) begin
	if(cnt_clk == 24999999) begin
		cnt_clk <= 0;
		clk1s <= ~clk1s;
	end
	else begin
		cnt_clk <= cnt_clk + 1;
	end		
end

endmodule //clk50_2_clk1s