module virtual_videomem (
	input clk,
	input rstn,
	input [7:0] ascii_key,
	input [7:0] scancode,
	input valid,
	input [9:0] h_addr,
	input [9:0] v_addr,
	output [23:0] vga_data
);

parameter font_color = 24'hffffff;
parameter back_color = 24'h000000;
parameter max_x = 30;
parameter max_y = 70;

reg [7:0] ram[3839:0]; // 3840, using for virtual video memory
reg [7:0] x, y;

reg [143:0] fonts[255:0];

wire [9:0] query_x, query_y, point_x, point_y;
assign query_x = (h_addr - 5) / 9;
assign query_y = v_addr[8:4];
assign point_x = (h_addr - 5) % 9;
assign point_y = v_addr[3:0];
assign vga_data = (h_addr < 5
					? back_color
					: (fonts[ram[{ query_x[6:0], query_y[4:0] }]][{ point_x[3:0], point_y[3:0]}] 
						? font_color
						: back_color));

always @(posedge clk or negedge rstn) begin
	if(rstn == 0) begin
		x = 8'h0;
		y = 8'h0;
	end
	else begin
		if(valid) begin
			ram[{ x[4:0], y[6:0] }] = ascii_key;
			if(y + 1 == max_y) begin
				y = 8'h0;
				if(x + 1 == max_x) begin
					x = 8'h0;
				end
				else begin
					x = x + 1;
				end
			end
			else begin
				y = y + 1;
			end
		end
	end
end

endmodule //virtual_videomem