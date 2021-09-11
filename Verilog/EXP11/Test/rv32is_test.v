`timescale 10ns/10ns

`include "../rv32is.v"

module rv32is_test;

	reg 			clock, reset;
	reg 	[31:0]	imemdataout, dmemdataout;
	wire 	[31:0]	imemaddr, dmemaddr, dmemdatain;
	wire 			imemclk, dmemrdclk, dmemwrclk, dmemwe;
	wire 	[2:0]	dmemop;
    wire 	[31:0] 	dbgdata;

    rv32is __rv32is(
		.clock(clock),
		.reset(reset),
		.imemaddr(imemaddr),
		.imemdataout(imemdataout),
		.imemclk(imemclk),
		.dmemaddr(dmemaddr),
		.dmemdataout(dmemdataout),
		.dmemdatain(dmemdatain),
		.dmemrdclk(dmemrdclk),
		.dmemwrclk(dmemwrclk),
		.dmemop(dmemop),
		.dmemwe(dmemwe),
		.dbgdata(dbgdata)
	);

    initial begin
        $display("start a test for Module RV32IS."); 	// 打印开始标记
        $dumpfile("rv32is_wave.vcd");                  // 指定记录模拟波形的文件
        $dumpvars(0, rv32is_test);                     // 指定记录的模块层级
		clock <= 0;
		reset <= 1;
		dmemdataout <= 0;
        #6000 $finish;                                  // 6000个单位时间后结束模拟
    end

	always begin
		#10 reset <= 0;
	end

	always begin
		#20 clock <= ~clock;
	end

    always begin
		imemdataout <= 32'h06400313; #40; // x6 = 100
		imemdataout <= 32'h00602023; #40; // watch x6
		imemdataout <= 32'h01400393; #40; // x7 = 20
		imemdataout <= 32'h00702023; #40; // watch x7
		imemdataout <= 32'h00730e33; #40; // x28 = x6 + x7;
		imemdataout <= 32'h00602023; #40; // watch x6
		imemdataout <= 32'h00702023; #40; // watch x7
		imemdataout <= 32'h00639463; #40; // if(x6 != x7) PC = PC + 8
    end

endmodule //clock_pulse