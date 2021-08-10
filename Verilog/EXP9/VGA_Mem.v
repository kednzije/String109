module VGA_Mem (
	input clk,
	input rstn, // unused
	input wren, // TODO: not using kb_valid
	input [3:0] w_ascii_addr_x,
	input [3:0] w_ascii_addr_y,
	input [7:0] w_ascii,
	input [9:0] r_ascii_addr_x, // 字符坐标
	input [9:0] r_ascii_addr_y,
	input [3:0] r_ascii_pixel_x, // 像素坐标
	input [3:0] r_ascii_pixel_y,
	output [23:0] vga_data
);

	// 8 * 70(x) * 64(y)
	reg [7:0] mem[4479:0]; // virtual video memory containing ascii codes, ram

	// 9(x) * 256(ascii) * 16(y)
	reg [8:0] fonts[4095:0]; // char's fonts, rom

	parameter font_color = 24'hFFFFFF;
	parameter back_color = 24'h000000;

	assign vga_data = (fonts[{ mem[{ r_ascii_addr_x[6:0], r_ascii_addr_y[5:0] }][7:0], r_ascii_pixel_y[3:0] }][r_ascii_addr_x[3:0]]) ? font_color : back_color;

	always @(posedge clk) begin
		if(wren) begin
			mem[{ w_ascii_addr_x[6:0], w_ascii_addr_y[5:0] }] = w_ascii;
		end
	end

endmodule //VGA_Mem