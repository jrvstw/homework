`timescale 1ns/1ps
`include "top.v"


//`define SEED 120
module tb_alu();


reg signed  [3:0]	A;
reg signed  [3:0]	B;
reg signed  [1:0]	OP;
reg 				CLK;
reg					RST;

wire signed [7:0]	OUT;
wire signed [7:0]	OUT_w;
top m1(A, B, OP, OUT,OUT_w, CLK, RST);

initial begin

	//$dumpfile("lab2.vcd");  // gtkwave
	//$dumpvars;
	CLK = 1'b0;
	#10 RST = 1;
	#20	OP = 2'b00;
		A = 4'd9;
		B = 4'd3;
	#20 RST = 0;
	#20 
		OP = 2'b01;
		A = 4'd9;
		B = 4'd3;

	#20 
		OP = 2'b10;
		A = 4'd8;
		B = 4'd1;

	#20 
		OP = 2'b11;
		A = 4'd8;
		B = 4'd1;

	#20 RST = 1;

	#20 $finish;


end

always #5 CLK = ~CLK;

initial begin
	$dumpfile("alu.vcd");
	$dumpvars;
end
endmodule
