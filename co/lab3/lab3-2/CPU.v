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
wire [31:0] DX_PC;
wire [4:0] DX_RD;
wire [31:0] A, B, Imm, JAddr;
wire [2:0] ALUctr;
wire ALUSrc;
wire Jump;
wire DX_Branch;
wire DX_RegWrite;
// EXECUTION wires
wire [4:0] XM_RD;
wire [31:0] XM_ALUout, BAddr;
wire XF_Branch;
wire XM_RegWrite;
// DATA_MEMORY wires
wire [4:0]	MW_RD;
wire [31:0] MW_ALUout;
wire MW_RegWrite;

/*============================== INSTRUCTION_FETCH  ==============================*/

INSTRUCTION_FETCH IF(
	.clk(clk),
	.rst(rst),
    .Jump(Jump),
    .JAddr(JAddr),
    .Branch(XF_Branch),
    .BAddr(BAddr),

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
    .MW_RegWrite(MW_RegWrite),

    .DX_PC(DX_PC),
	.RD(DX_RD),
	.A(A),
	.B(B),
    .Imm(Imm),
    .JAddr(JAddr),
	.ALUctr(ALUctr),
    .ALUSrc(ALUSrc),
    .Jump(Jump),
    .Branch(DX_Branch),
    .DX_RegWrite(DX_RegWrite)
);

/*==============================     EXECUTION  	==============================*/

EXECUTION EXE(
	.clk(clk),
	.rst(rst),
	.A(A),
	.B(B),
    .Imm(Imm),
    .DX_PC(DX_PC),
	.DX_RD(DX_RD),
	.ALUctr(ALUctr),
    .ALUSrc(ALUSrc),
    .DX_Branch(DX_Branch),
    .DX_RegWrite(DX_RegWrite),


	.ALUout(XM_ALUout),
    .BAddr(BAddr),
	.XM_RD(XM_RD),
    .XF_Branch(XF_Branch),
    .XM_RegWrite(XM_RegWrite)
);

/*==============================     DATA_MEMORY	==============================*/

MEMORY MEM(
	.clk(clk),
	.rst(rst),
	.XM_RD(XM_RD),
	.ALUout(XM_ALUout),
    .XM_RegWrite(XM_RegWrite),

	.MW_RD(MW_RD),
	.MW_ALUout(MW_ALUout),
    .MW_RegWrite(MW_RegWrite)
);

endmodule
