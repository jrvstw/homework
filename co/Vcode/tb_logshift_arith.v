`timescale 1ns/1ps
`include "log_shift_arith.v"

module tb_log_shift_arith;
reg  signed[15:0] din;
reg	  [3:0] shamt;
wire  [15:0] dout;

log_shift_arith m2(din, shamt, dout);

initial begin
	$dumpfile("exam2.vcd");
	$dumpvars;
	din = 0;
	shamt = 0;
	#10 din = 16'd1024;
		shamt = 4'd1;
	#10	
		shamt = 4'd5;
	#10	
		shamt = 4'd11;
	
	#10 din = -16'd1024;
		shamt = 4'd1;
	#10	
		shamt = 4'd5;
	#10	
		shamt = 4'd11;
	#20 $finish;

end

endmodule
