module tm(input  clk,
	input  [7:0] datain,
	input  reset,
	output reg [7:0] dataout,
	output reg move,
	output reg halt
	);
parameter s0 = 0, s1 = 1, s2 = 2, s3 = 3, s4 = 4, s7 = 7;
reg [2:0] state;

always @(posedge clk) begin
	if(reset) begin
		state = s0;
		halt = 0;
	end else begin
		case (state)
			s0: begin
				halt = 0;
				if(datain == 8'h0) begin
					state = s7;
					dataout = 8'h54;
					move = 0;
				end
				if(datain == 8'h28) begin
					state = s1;
					dataout = 8'h0;
					move = 0;
				end
				if(datain == 8'h29) begin
					state = s7;
					dataout = 8'h46;
					move = 0;
				end
			end
			s1: begin
				halt = 0;
				if(datain == 8'h0) begin
					state = s7;
					dataout = 8'h46;
					move = 0;
				end
				if(datain == 8'h28) begin
					state = s1;
					dataout = 8'h28;
					move = 0;
				end
				if(datain == 8'h29) begin
					state = s2;
					dataout = 8'h29;
					move = 0;
				end
			end
			s2: begin
				halt = 0;
				if(datain == 8'h0) begin
					state = s3;
					dataout = 8'h0;
					move = 1;
				end
				if(datain == 8'h28) begin
					state = s7;
					dataout = 8'h46;
					move = 0;
				end
				if(datain == 8'h29) begin
					state = s2;
					dataout = 8'h29;
					move = 0;
				end
			end
			s3: begin
				halt = 0;
				if(datain == 8'h29) begin
					state = s4;
					dataout = 8'h0;
					move = 1;
				end
			end
			s4: begin
				halt = 0;
				if(datain == 8'h0) begin
					state = s0;
					dataout = 8'h0;
					move = 0;
				end
				if(datain == 8'h28) begin
					state = s4;
					dataout = 8'h28;
					move = 1;
				end
				if(datain == 8'h29) begin
					state = s4;
					dataout = 8'h29;
					move = 1;
				end
			end
			s7: begin
				halt = 1;
			end
			default: begin
				halt = 1;
			end
		endcase
	end
end

endmodule