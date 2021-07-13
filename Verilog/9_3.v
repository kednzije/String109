module attendance(
	input [127:0] name,
	input clk,
	input rst,
	input [1:0] cmd,
	output reg [127:0] dataout
);

reg [127:0] namexor;

always @(posedge clk) begin
	if(rst) begin
		namexor = 128'h0;
	end else if(cmd == 0) begin
		dataout = namexor;
	end else begin
		namexor = namexor ^ name;
	end
end

endmodule