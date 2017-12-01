`timescale 1ns / 1ps
`include "maxmin.v"
module tb_acc;
	reg clk,rst;
	reg signed[15:0] din;
	wire [15:0] dout;
	integer i;
	maxmin x1(clk,rst,din,dout,rdy);
	
	initial begin
		$dumpfile("exam4.vcd");
		$dumpvars;
		clk = 0;
		din = 0;
	    rst = 0;
		#10 rst = 1;
			for(i=1;i<=16;i=i+1) begin
				din = i*((-1)**(i-1));
				#20;
			end
		#300 $finish;
	end
	always #10 clk = ~clk;
endmodule