`timescale 1ns/1ps
`include "INSTRUCTION_FETCH.v"
`include "INSTRUCTION_DECODE.v"
`include "EXECUTION.v"
`include "MEMORY.v"

module CPU(
	clk, rst,
	input_number
);

input clk, rst;
input [31:0] input_number;
/*============================== Wire  ==============================*/
// INSTRUCTION_FETCH wires
wire [31:0] FD_PC, FD_IR;
// INSTRUCTION_DECODE wires
wire [31:0] DX_PC, JAddr;
wire Jump;
wire DX_Branch;
wire DX_MemToReg;
wire DX_MemWrite;
wire DX_RegWrite;
wire lhWrite;
wire lhRead;
wire mflo;
wire ALUSrc;
wire [2:0] ALUCtr;
wire [4:0] DX_RD;
wire [31:0] A, B, Imm;
// EXECUTION wires
wire [31:0] BAddr;
wire XF_Branch;
wire XM_MemToReg;
wire XM_MemWrite;
wire XM_RegWrite;
wire [4:0] XM_RD;
wire [31:0] XM_ALUout, XM_B;
// DATA_MEMORY wires
wire MW_RegWrite;
wire [4:0]	MW_RD;
wire [31:0] MW_ALUout;

/*============================== INSTRUCTION_FETCH  ==============================*/

INSTRUCTION_FETCH IF(
	.clk(clk),
	.rst(rst),
    .Jump(Jump),
    .Branch(XF_Branch),
    .JAddr(JAddr),
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
    .MW_RegWrite(MW_RegWrite),
	.MW_RD(MW_RD),
	.MW_ALUout(MW_ALUout),

    .DX_PC(DX_PC),
    .JAddr(JAddr),
    .Jump(Jump),
    .Branch(DX_Branch),
    .DX_MemToReg(DX_MemToReg),
    .DX_MemWrite(DX_MemWrite),
    .DX_RegWrite(DX_RegWrite),
    .lhWrite(lhWrite),
    .lhRead(lhRead),
    .mflo(mflo),
    .ALUSrc(ALUSrc),
	.ALUCtr(ALUCtr),
	.RD(DX_RD),
	.A(A),
	.B(B),
    .Imm(Imm)
);

/*==============================     EXECUTION  	==============================*/

EXECUTION EXE(
	.clk(clk),
	.rst(rst),
    .DX_PC(DX_PC),
    .DX_Branch(DX_Branch),
    .DX_MemToReg(DX_MemToReg),
    .DX_MemWrite(DX_MemWrite),
    .DX_RegWrite(DX_RegWrite),
    .lhWrite(lhWrite),
    .lhRead(lhRead),
    .mflo(mflo),
    .ALUSrc(ALUSrc),
	.ALUCtr(ALUCtr),
	.DX_RD(DX_RD),
	.A(A),
	.B(B),
    .Imm(Imm),


    .BAddr(BAddr),
    .XF_Branch(XF_Branch),
    .XM_MemToReg(XM_MemToReg),
    .XM_MemWrite(XM_MemWrite),
    .XM_RegWrite(XM_RegWrite),
	.XM_RD(XM_RD),
	.ALUout(XM_ALUout),
    .XM_B(XM_B)
);

/*==============================     DATA_MEMORY	==============================*/

MEMORY MEM(
	.clk(clk),
	.rst(rst),
    .XM_MemToReg(XM_MemToReg),
    .XM_MemWrite(XM_MemWrite),
    .XM_RegWrite(XM_RegWrite),
	.XM_RD(XM_RD),
	.ALUout(XM_ALUout),
    .XM_B(XM_B),
    .input_number(input_number),

	.MW_RD(MW_RD),
	.MW_ALUout(MW_ALUout),
    .MW_RegWrite(MW_RegWrite)
);

endmodule
