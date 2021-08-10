module Cursor_Ctrl (
	input clk,
	input rstn,
	input [7:0] ascii_code,
	input [7:0] scan_code,
	input kb_valid,
	output reg [3:0] cursor_x,
	output reg [3:0] cursor_y
);

parameter cursor_x_total = 70;
parameter cursor_y_total = 30;

initial begin
	cursor_x <= 0;
	cursor_y <= 0;
end

always @(posedge clk or negedge rstn) begin
	if(rstn == 1'b0) begin
		cursor_x <= 0;
		cursor_y <= 0;
	end
	else begin
		if(kb_valid) begin
			if(cursor_x + 1 == cursor_x_total) begin
				if(cursor_y + 1 == cursor_y_total) begin
					cursor_y <= 0;
					cursor_x <= 0;
				end
				else begin
					cursor_y <= cursor_y + 1;
					cursor_x <= 0;
				end
			end
			else begin
				cursor_x <= cursor_x + 1;
			end
		end
	end
end

endmodule //Cursor_Ctrl