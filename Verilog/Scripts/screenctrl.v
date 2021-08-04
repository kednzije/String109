module screenctrl (
	input clk,
	input [7:0] scancode,
	input [1:0] kb_state,
	output reg [9:0] x,
	output reg [9:0] y,
	output reg [11:0] pixel 
);

wire [7:0] ascii;
// scancode_ram scancode_r(clk, scancode, kb_state, ascii);

always @(posedge clk) begin
	if(scancode[7:0] == 8'h66) begin
		if(| y) begin
			y <= y - 1;
		end
		else begin
			x <= 0; // to be explained
		end
		pixel <= 12'h0;
	end
	else if(scancode[7:0] == 8'h5A) begin
		x <= x + 1;
		y <= 0;
	end
end

endmodule //screenctrl