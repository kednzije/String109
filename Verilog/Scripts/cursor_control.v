module cursor_control (
	input clk,
	input [7:0] scancode,
	input [7:0] asciicode,
	input valid,
	output reg [9:0] x,
	output reg [9:0] y,
	output reg [7:0] data,
	output reg wr,
	output reg reset
);

parameter max_xi = 70;
parameter max_yi = 30;
parameter height = 16;
parameter width = 9;

reg [6:0] xi, yi;
reg [29:0] cr; 

initial begin
	x = 0;
	y = 5;
	xi = 0;
	yi = 0;
	data = 8'h0;
	wr = 0;
	reset = 0;
	cr = 0;
end

always @(posedge clk) begin
	if(valid) begin
		if (asciicode[7:0] == 8'h08) begin // Backspace

		end
		else if(asciicode[7:0] == 8'h0D) begin // Enter
			
		end
		else begin // print char
			if(yi + 1 == max_yi) begin
				yi = 0;
				y = 0;
				if(xi + 1 == max_xi) begin
					reset = 1;
					xi = 0;
					x = 5;
				end
				else begin
					reset = 0;
					xi = xi + 1;
					x = x + height;
				end
			end
			else begin
				reset = 0;
				yi = yi + 1;
				y = y + width;
			end
			data = asciicode;
			wr = 1;
		end
	end
end

endmodule //cursor_control