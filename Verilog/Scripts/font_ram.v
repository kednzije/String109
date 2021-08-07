module font_ram (
	input [7:0] addr,
	output wire [143:0] font
);

reg [143:0] fonts[255:0];

initial begin
	// $readmemh
end

assign font = fonts[addr];

endmodule //font_ram