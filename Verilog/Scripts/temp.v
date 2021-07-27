module keyboard(input clk,
	input clrn,
	input ps2_clk,
	input ps2_data,
	output reg [7:0] key_count,
	output reg [7:0] cur_key,
	output [7:0] ascii_key);

// add your definitions here
reg [7:0] data;
reg [7:0] lastdata;
reg ready, nextdata_n, overflow;
reg [1:0] state;

parameter S0 = 0;
parameter S1 = 1;
parameter S2 = 2;
parameter S3 = 3;

//----DO NOT CHANGE BEGIN----
//scancode to ascii conversion, will be initialized by the testbench
scancode_ram myram(clk, cur_key, ascii_key);
//PS2 interface, you may need to specify the inputs and outputs
ps2_keyboard mykey(clk, clrn, ps2_clk, ps2_data, data, ready, nextdata_n, overflow);
//---DO NOT CHANGE END-----

// add you code here
always @ (state) begin
    case(state)
    S1: begin
        lastdata = 0;
        cur_key = 0;
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
        key_count = 0;
        cur_key = 0;
        lastdata = 0;
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


//standard ps2 interface, you can keep this
module ps2_keyboard(clk,clrn,ps2_clk,ps2_data,data,ready,nextdata_n,overflow);
    input clk,clrn,ps2_clk,ps2_data;
	 input nextdata_n;
    output [7:0] data;
    output reg ready;
    output reg overflow;     // fifo overflow  
    // internal signal, for test
    reg [9:0] buffer;        // ps2_data bits
    reg [7:0] fifo[7:0];     // data fifo
	 reg [2:0] w_ptr,r_ptr;   // fifo write and read pointers	
    reg [3:0] count;  // count ps2_data bits
    // detect falling edge of ps2_clk
    reg [2:0] ps2_clk_sync;
    
    always @(posedge clk) begin
        ps2_clk_sync <=  {ps2_clk_sync[1:0],ps2_clk};
    end

    wire sampling = ps2_clk_sync[2] & ~ps2_clk_sync[1];
    
    always @(posedge clk) begin
        if (clrn == 0) begin // reset 
            count <= 0; w_ptr <= 0; r_ptr <= 0; overflow <= 0; ready<= 0;
        end 
		else if (sampling) begin
            if (count == 4'd10) begin
                if ((buffer[0] == 0) &&  // start bit
                    (ps2_data)       &&  // stop bit
                    (^buffer[9:1])) begin      // odd  parity
                    fifo[w_ptr] <= buffer[8:1];  // kbd scan code
                    w_ptr <= w_ptr+3'b1;
                    ready <= 1'b1;
                    overflow <= overflow | (r_ptr == (w_ptr + 3'b1));
                end
                count <= 0;     // for next
            end else begin
                buffer[count] <= ps2_data;  // store ps2_data 
                count <= count + 3'b1;
            end      
        end
        if ( ready ) begin // read to output next data
				if(nextdata_n == 1'b0) //read next data
				begin
				   r_ptr <= r_ptr + 3'b1; 
					if(w_ptr==(r_ptr+1'b1)) //empty
					     ready <= 1'b0;
				end           
        end
    end

    assign data = fifo[r_ptr];
endmodule 

//simple scancode converter
module scancode_ram(clk, addr,outdata);
input clk;
input [7:0] addr;
output reg [7:0] outdata;
//Do not change the name of this ram, testbench will initialize this
reg [7:0] ascii_tab[255:0];

always @(posedge clk)
begin
      outdata <= ascii_tab[addr];
end

endmodule