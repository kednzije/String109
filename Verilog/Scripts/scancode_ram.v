//simple scancode converter
module scancode_ram(clk, addr,outdata);
input clk;
input [7:0] addr;
output reg [7:0] outdata;

(* ram_init_file = "ascii_tab.mif" *) reg [7:0] ascii_tab[255:0];

always @(posedge clk)
begin
      outdata <= ascii_tab[addr];
end

endmodule