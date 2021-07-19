 module regfile(input  [3:0]  ra,
	input  [3:0]  rb,
	input  [3:0]  rw,
	input  [7:0] wrdata,
	input  regwr,
	input  wrclk,
	output [7:0] outa,
	output [7:0] outb
	);
	
	//The regfile
	reg [7:0] regs[3:0];	
	
	always @ (posedge wrclk) begin
		if(regwr && rw != 0) begin
			regs[rw] = wrdata;
		end
	end

	assign outa = regs[ra];
	assign outb = regs[rb];
	
endmodule