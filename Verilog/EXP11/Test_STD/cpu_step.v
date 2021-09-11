`include "../rv32is.v"
`include "./dmem.v"
`include "./testmem.v"
`include "./testdmem.v"

`timescale 1 ns / 10 ps
module cpu_single_vlg_tst();

integer numcycles;  //number of cycles in test

reg clk,reset;  //clk and reset signals

reg[8*8:1] testcase; //name of testcase

// CPU declaration

// signals
wire [31:0] iaddr,idataout;
wire iclk;
wire [31:0] daddr,ddataout,ddatain;
wire drdclk, dwrclk, dwe;
wire [2:0]  dop;
wire [31:0] cpudbgdata;



//main CPU
rv32is mycpu(.clock(clk), 
             .reset(reset), 
				 .imemaddr(iaddr), .imemdataout(idataout), .imemclk(iclk), 
				 .dmemaddr(daddr), .dmemdataout(ddataout), .dmemdatain(ddatain), .dmemrdclk(drdclk), .dmemwrclk(dwrclk), .dmemop(dop), .dmemwe(dwe), 
				 .dbgdata(cpudbgdata));

				  
//instruction memory, no writing
testmem instructions(
	.address(iaddr[17:2]),
	.clock(iclk),
	.data(32'b0),
	.wren(1'b0),
	.q(idataout));
	

//data memory	
dmem datamem(.addr(daddr), 
             .dataout(ddataout), 
				 .datain(ddatain), 
				 .rdclk(drdclk), 
				 .wrclk(dwrclk), 
				 .memop(dop), 
				 .we(dwe));

//useful tasks
task step;  //step for one cycle ends 1ns AFTER the posedge of the next cycle
	begin
		#900  clk=1'b0; 
		#1000 clk=1'b1;
		numcycles = numcycles + 1;	
		#100 ;
	end
endtask
				  
task stepn; //step n cycles
   input integer n; 
	integer i;
	begin
		for (i =0; i<n ; i=i+1)
			step();
	end
endtask

task resetcpu;  //reset the CPU and the test
	begin
		reset = 1'b1; 
		step();
		#500 reset = 1'b0;
		numcycles = 0;
	end
endtask

task loadtestcase;  //load intstructions to instruction mem
	begin
		$readmemh({testcase, ".hex"},instructions.ram);
		$display("~~~ Begin test case %s ~~~", testcase);
	end
endtask
	
task checkreg;//check registers
   input [4:0] regid;
	input [31:0] results; 
	reg [31:0] debugdata;
	begin
	    debugdata=mycpu.myregfile.regs[regid]; //wait for signal to settle
		 if(debugdata==results)
		 	begin
				$display("~~~ OK: end of cycle %3d reg %h need to be %h, get %h", numcycles, regid, results, debugdata);
			end
		else	
			begin
				$display("~~~ Error: end of cycle %3d reg %h need to be %h, get %h", numcycles, regid, results, debugdata);
			 end
	end
endtask

task checkmem;//check registers
   input [31:0] inputaddr;
   input [31:0] results;	
	reg [31:0] debugdata;
	reg [14:0] dmemaddr;
	begin
	    dmemaddr=inputaddr[16:2];
	    debugdata=datamem.mymem.ram[dmemaddr]; 
		 if(debugdata==results)
		 	begin
				$display("~~~ OK: end of cycle %3d mem addr= %h need to be %h, get %h", numcycles, inputaddr, results, debugdata);
			end
		else	
			begin
				$display("~~~ Error: end of cycle %3d mem addr= %h need to be %h, get %h", numcycles, inputaddr, results, debugdata);
			 end
	end
endtask

task checkpc;//check PC
	input [31:0] results; 
	begin
		 if(cpudbgdata==results)
		 	begin
				$display("~~~ OK: end of cycle %3d PC/dbgdata need to be %h, get %h", numcycles,  results, cpudbgdata);
			end
		else	
			begin
				$display("~~~ Error: end of cycle %3d PC/dbgdata need to be %h, get %h", numcycles, results, cpudbgdata);
			 end
	end
endtask

integer maxcycles =10000;


task checkmagnum;
    begin
	    if(numcycles>maxcycles)
		 begin
		   $display("~~~ Error:test case %s does not terminate!", testcase);
		 end
		 else if(mycpu.myregfile.regs[10]==32'hc0ffee)
		    begin
		       $display("~~~ OK:test case %s finshed OK at cycle %d.", testcase, numcycles-1);
		    end
		 else if(mycpu.myregfile.regs[10]==32'hdeaddead)
		 begin
		   $display("~~~ ERROR:test case %s finshed with error in cycle %d.", testcase, numcycles-1);
		 end
		 else
		 begin
		    $display("~~~ ERROR:test case %s unknown error in cycle %d.", testcase, numcycles-1);
		 end
	 end
endtask

task loaddatamem;
    begin
	     $readmemh({testcase, "_d.hex"},datamem.mymem.ram);
	 end
endtask

	
initial begin:TestBench
	$display("start a standard test for Module RV32IS."); 	// 打印开始标记
	$dumpfile("rv32is_wave.vcd");                  // 指定记录模拟波形的文件
	$dumpvars(0, cpu_single_vlg_tst);                     // 指定记录的模块层级
    #800
    // output the state of every instruction
    testcase = "add";
	//addi t1,zero,100
    //addi t2,zero,20
    //add t3,t1,t2
    loadtestcase();
    resetcpu();
    step();
    checkreg(6,100);
	checkpc(32'h4);
    step();
    checkreg(7,20);
	checkpc(32'h8);
    step();
	checkreg(28,120);		
	testcase = "alu";
	//addi t1,zero,79
	//addi t2,zero,3
	//sub  t3,t1,t2  
	//and  t3,t1,t2
	//sll  t3,t1,t2
	//slt  t3,t1,t2
	//slt  t3,t2,t1
	//xor  t3,t2,t1
	//srl  t3,t1,t2
	//or   t3,t1,t2
	//addi t1,zero,-3
    //add  t3,t1,t2
    //sra  t3,t1,t2
    //srl  t3,t1,t2
	loadtestcase();
	resetcpu();
	step();
	checkreg(6,79); //t1=79
	step();
	checkreg(7,3);  //t2=3
	step();
	checkreg(28,76); //t3=76
	step();
	checkreg(28,3); //t3=3
	step();
	checkreg(28,632); //t3=632
	step();
	checkreg(28,0); //t3=0
	step();
	checkreg(28,1); //t3=1
	step();
	checkreg(28,76); //t3=76
	step();
	checkreg(28,9); //t3=9
	step();
	checkreg(28,79); //t3=79
	step();
	checkreg(6,-79); //t1=-79,ffffffb1, 10110001
	step();
	checkreg(28,-76); //t3=-76
	step();
	checkreg(28,32'hfffffff6); //t3=fffffff6, 11110110
	step();
	checkreg(28,32'h1ffffff6); //t3=1ffffff6
	step();
	checkreg(28,1); // t3=1, slt -79<3
	step();
	checkreg(28,0); //t3=0 sltu ffffffb1>3
	testcase = "mem";
	//lui a0, 0x00008
	//addi a0, a0,16
	//addi t1,zero, 1234
	//sw t1,4(a0)
	//lw t2,4(a0)
	//sw zero,8(a0)
	//addi t1,zero, 255
	//sb   t1,8(a0)
	//lb   t2,8(a0)
	//lbu  t2,8(a0)
	//sb   t1,9(a0)
	//lh   t2,8(a0)
	//lhu  t2,8(a0)
	//lb   t2,9(a0)
	//lb   t2,10(a0)
	//sw   zero,12(a0)
	//addi t1,zero, 0x78
	//sb   t1,12(a0)
	//addi t1,zero, 0x56
	//sb   t1,13(a0)
	//addi t1,zero, 0x34
	//sb   t1,14(a0)
	//addi t1,zero, 0x12
	//sb   t1,15(a0)
	//lw   t2,12(a0)
	loadtestcase();
	resetcpu();
	step();
	checkreg(10,32'h8000);
	step();
	checkreg(10,32'h8010);
	step();
	checkreg(6,32'd1234);
	step();
	checkmem(32'h8014,32'd1234);
	step();
	checkreg(7,32'd1234);
	step();
	checkmem(32'h8018,32'd0);
	step();
	checkreg(6,32'd255);
	step();
	checkmem(32'h8018,32'hff);
	step();
	checkreg(7,32'hffffffff);
	step();
	checkreg(7,32'hff);
	step();
	checkmem(32'h8018,32'hffff);
	step();
	checkreg(7,32'hffffffff);
	step();
	checkreg(7,32'hffff);
	step();
	checkreg(7,32'hffffffff);
	step();
	checkreg(7,32'h0);
	step();
	checkmem(32'h801c,32'h0);
	step();
	checkreg(6,32'h78);
	step();
	checkmem(32'h801c,32'h78);
	step();
	checkreg(6,32'h56);
	step();
	checkmem(32'h801c,32'h5678);
	step();
	checkreg(6,32'h34);
	step();
	checkmem(32'h801c,32'h345678);
	step();
	checkreg(6,32'h12);
	step();
	checkmem(32'h801c,32'h12345678);
	step();
	checkreg(7,32'h12345678);
	testcase = "branch";
	//	addi t0,zero,100
	//	addi t1,zero,-2
	//	beq  t1,t0, error
	//	bne  t0,t1, bnenext
	//	j    error
	//bnenext: 	blt  t0,t1,error
	//	bge  t1,t0,error
	//	bltu t0,t1,bltunext
	//	j    error
	//bltunext:	bgeu t0,t1,error
	//	jal  ra, func
	//error: 	li   a0,0xdeaddead
	//	j    finish
	//right:	li   a0,0xc0ffee
	//	j    finish
	//func:	addi t0,zero,123
	//	jalr t1,ra,12
	//finish:	nop
	loadtestcase();
	resetcpu();
	step();
	checkreg(5,32'd100);
	step();
	checkreg(6,32'hfffffffe);
	step();
	checkpc(32'hc);
	step();
	checkpc(32'h14);
	step();
	checkpc(32'h18);
	step();
	checkpc(32'h1c);
	step();
	checkpc(32'h24);
	step();
	checkpc(32'h28);
	step();
	checkpc(32'h44);
	checkreg(1,32'h2c);
	step();
	checkpc(32'h48);
	checkreg(5,32'd123);
	step();
	checkpc(32'h38);
	step();
	checkpc(32'h3c);
	step();
	checkreg(10,32'hc0ffee);
	step();
	checkpc(32'h4c);
	$stop;
end

				  
endmodule