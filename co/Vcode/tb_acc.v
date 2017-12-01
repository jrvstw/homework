`timescale 1ns / 1ps
`include "acc.v"
module tb_acc;
	reg clk,rst,en;
	reg [15:0] din;
	wire [15:0] dout;
	integer i;
	acc a1(din,dout,clk,rst,en);
	
	initial begin
		$dumpfile("exam3.vcd");
		$dumpvars;
		clk = 0;
		din = 0;
		#10 rst = 0;
		#10 rst = 1;
		#10 en = 1;
			for(i=1;i<=100;i=i+1) begin
				din = i*((-1)**(i-1));
				#20;
			end
			en = 0;
		#500 $finish;
	end
	always #10 clk = ~clk;
endmodule