module dfa(input  clk,
	input  [7:0] data,
	input  reset,
	output reg result
	);

parameter s0 = 0, s1 = 1, s2 = 2, s3 = 3, s4 = 4, s5 = 5;
reg [2:0] state;

always @(state) begin
	case (state)
		s0: result = 0;
		s1: result = 0;
		s2: result = 0;
		s3: result = 0;
		s4: result = 0;
		s5: result = 1;
		default: result = 0;
	endcase
end

always @(posedge clk) begin
	if(reset) begin
		state = s0;
	end else begin
		case (state)
			s0: 
				if (data == 8'h0) begin
					state = s0;
				end else if(data == 8'h4e || data == 8'h6e) begin
					state = s1;
				end else begin
					state = s3;
				end
			s1: 
				if (data == 8'h0) begin
					state = s5;
				end else if(data == 8'h4e || data == 8'h6e) begin
					state = s4;
				end else begin
					state = s2;
				end
			s2: 
				if (data == 8'h0) begin
					state = s0;
				end else if(data == 8'h4e || data == 8'h6e) begin
					state = s3;
				end else begin
					state = s1;
				end
			s3: 
				if (data == 8'h0) begin
					state = s0;
				end else if(data == 8'h4e || data == 8'h6e) begin
					state = s2;
				end else begin
					state = s4;
				end
			s4: 
				if (data == 8'h0) begin
					state = s0;
				end else if(data == 8'h4e || data == 8'h6e) begin
					state = s1;
				end else begin
					state = s3;
				end
			s5: 
				if (data == 8'h0) begin
					state = s0;
				end else if(data == 8'h4e || data == 8'h6e) begin
					state = s1;
				end else begin
					state = s3;
				end
			default: 
				if (data == 8'h0) begin
					state = s0;
				end else if(data == 8'h4e || data == 8'h6e) begin
					state = s1;
				end else begin
					state = s3;
				end
		endcase
	end
end

endmodule