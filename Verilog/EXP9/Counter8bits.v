module Counter8bits (
	input clk,
	input rstn,
	output reg [7:0] count,
	output reg carry 
);

parameter max_cnt = 100;

always @(posedge clk or negedge rstn) begin
	if(rstn == 1'b0) begin
		count <= 0;
		carry <= 0;
	end
	else begin
		if(count + 1 == max_cnt) begin
			count <= 0;
			carry <= 1;
		end
		else begin
			count <= count + 1;
			carry <= 0;
		end
	end
end

endmodule //Counter8bits