`timescale 1ns / 1ps
module fulladder_test;
	reg 	[15:0]a, b;
	reg		cin;	
	wire	[15:0]sum;
	wire    cout;
	_16bit_adder_Continuous DUT(sum, cout, a, b, cin);
	initial
	begin
		$dumpfile("16bit_adder_continuous.vcd");
		$dumpvars;
		a = 16'b1111111100000000;
		b = 16'b1111111111111111;
		cin = 1'b1;
	end
	always #1 
	begin
		a = (a << 1 | cin);
		$monitor("%4dns monitor: a=%d b=%d cin=%d sum=%d cout=%d", $stime, a, b, cin, sum, cout);
	end
	always #2 b = b >> 2;
	always #3 cin = ~cin;
	initial #16 $finish;
endmodule