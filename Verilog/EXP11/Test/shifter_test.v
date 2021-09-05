`timescale 10ns/10ns

`include "../Shifter.v"

module shifter_test;
    
    reg     [31:0]  a, b;
    wire    [31:0]  c;
    reg             l_or_r, a_or_h;
    Shifter shifter(
        .dataa(a),
        .datab(b),
        .l_or_r(l_or_r),
        .a_or_h(a_or_h),
        .result(c)
    );

    initial begin
        $display("start a test for Module Shifter.");   // 打印开始标记
        $dumpfile("shifter_wave.vcd");                  // 指定记录模拟波形的文件
        $dumpvars(0, shifter_test);                     // 指定记录的模块层级
        #6000 $finish;                                  // 6000个单位时间后结束模拟
    end

    always begin
        a <= -8;
        b <= 2;
        l_or_r <= 0;
        a_or_h <= 0;
        #20;

        l_or_r <= 1;
        a_or_h <= 0;
        #20;

        l_or_r <= 0;
        a_or_h <= 1;
        #20;

        l_or_r <= 1;
        a_or_h <= 1;
        #20;
    end

endmodule //clock_pulse