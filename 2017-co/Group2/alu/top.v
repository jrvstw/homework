`timescale 1ns/1ps
`include "alu.v"
module top( A, B, OP, OUT,OUT_w, CLK, RST );

	input CLK,RST;
    input   [3:0] A, B;
    input   [1:0] OP;
    output  [7:0] OUT;
	output  [7:0] OUT_w;
	wire  [7:0] OUT;
	assign OUT_w = OUT;
    ALU FUNCTION(    
        .Data_A(A),
        .Data_B(B),
        .OP_Code(OP),
		.ALU_RST(RST),
        .ALU_CLK(CLK),
		
		.Data_Out(OUT)
    );

endmodule
