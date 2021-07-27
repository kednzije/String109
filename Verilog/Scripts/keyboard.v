module keyboard(input clk,
	input clrn,
	input ps2_clk,
	input ps2_data,
	output reg [7:0] key_count,
	output reg [7:0] cur_key,
	output [7:0] ascii_key,
	output ready,
	output overflow,
	output sampling);

// add your definitions here
reg [7:0] data;
reg [7:0] lastdata;
reg nextdata_n;
reg [1:0] state;

parameter S0 = 0;
parameter S1 = 1;
parameter S2 = 2;
parameter S3 = 3;

//scancode to ascii conversion
scancode_ram scancode_r(clk, cur_key, ascii_key);
//PS2 interface
ps2_keyboard ps2_kb(clk, clrn, ps2_clk, ps2_data, data, ready, nextdata_n, overflow, sampling);

always @ (state) begin
	 case(state)
		 S1: begin
			  lastdata = 0;
			  cur_key = 0;
			  if(clrn == 0) begin
					key_count = 0;
			  end
		 end
		 S0: begin
			  key_count = key_count + 1;
			  lastdata = data;
			  cur_key = data;
		 end
		 S2: begin
			  lastdata = data;
			  cur_key = data;
		 end
		 S3: begin
			  lastdata = 0;
			  cur_key = 0;
		 end
		 default: begin
			  lastdata = 0;
			  cur_key = 0;
		 end
	 endcase
end

always @ (ready) begin
    if(clrn == 0) begin
        state = S1;
        nextdata_n = 1;
    end
    else if(ready && !overflow) begin
        nextdata_n = 0;

        case(state)
        S1: if(data != 8'hF0) state = S0; else state = S0;
        S0: if(data == 8'hF0) state = S3; else state = S2;
        S2: if(data == 8'hF0) state = S3; else state = S2;
        S3: if(data != 8'hF0) state = S1; else state = S3;
        endcase

    end
    else begin
        nextdata_n = 1;
    end
end

endmodule
