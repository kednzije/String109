module clk50divider (
	input clk50,
	input [31:0] T, // ms
	output reg clk
);

reg [31:0] cnt_clk;

initial begin
	cnt_clk = 0;
	clk = 0;
end

always @(posedge clk50) begin
	if(cnt_clk == 50000 * T / 2 - 1) begin
		cnt_clk <= 0;
		clk <= ~clk;
	end
	else begin
		cnt_clk <= cnt_clk + 1;
	end		
end

endmodule //clk50divider