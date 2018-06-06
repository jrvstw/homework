`timescale 1ns/1ps

`include "INSTRUCTION_FETCH.v"
`include "INSTRUCTION_DECODE.v"
`include "EXECUTION.v"
`include "MEMORY.v"

module CPU(
	clk,
	rst
);
input clk, rst;
/*============================== Wire  ==============================*/
// INSTRUCTION_FETCH wires
wire [31:0] FD_PC, FD_IR;
// INSTRUCTION_DECODE wires
wire [31:0] A, B, C;
wire [4:0] DX_RD;
wire [2:0] ALUctr;
// EXECUTION wires
wire [31:0] XM_ALUout;
wire [4:0] XM_RD;
// DATA_MEMORY wires
wire [31:0] MW_ALUout;
wire [4:0]	MW_RD;

wire [31:0] XM_B;
wire [5:0] DX_CTRL;
wire [5:0] XM_CTRL;
wire [5:0] MW_CTRL;

/*============================== INSTRUCTION_FETCH  ==============================*/

INSTRUCTION_FETCH IF(
	.clk(clk),
	.rst(rst),

	.PC(FD_PC),
	.IR(FD_IR)
);

/*============================== INSTRUCTION_DECODE ==============================*/

INSTRUCTION_DECODE ID(
	.clk(clk),
	.rst(rst),
	.PC(FD_PC),
	.IR(FD_IR),
	.MW_RD(MW_RD),
	.MW_ALUout(MW_ALUout),
    .MW_CTRL(MW_CTRL),

	.A(A),
	.B(B),
    .C(C),
	.RD(DX_RD),
	.ALUctr(ALUctr),
    .CTRL(DX_CTRL)
);

/*==============================     EXECUTION  	==============================*/

EXECUTION EXE(
	.clk(clk),
	.rst(rst),
	.A(A),
	.B(B),
    .C(C),
	.DX_RD(DX_RD),
	.ALUctr(ALUctr),
    .DX_CTRL(DX_CTRL),


	.ALUout(XM_ALUout),
	.XM_RD(XM_RD),
    .XM_B(XM_B),
    .XM_CTRL(XM_CTRL)
);

/*==============================     DATA_MEMORY	==============================*/

MEMORY MEM(
	.clk(clk),
	.rst(rst),
	.ALUout(XM_ALUout),
	.XM_RD(XM_RD),
    .XM_B(XM_B),
    .XM_CTRL(XM_CTRL),

	.MW_ALUout(MW_ALUout),
	.MW_RD(MW_RD),
    .MW_CTRL(MW_CTRL)
);

endmodule
