`timescale 1ns / 1ps
module _16bit_adder_Continuous (sum, cout, a, b, cin);
//port declaration

	input [15:0] a, b;
    input cin;
    output [15:0] sum;
    output cout;


// behavior description
	assign {cout,sum} = a+b+cin;
	
endmodule
