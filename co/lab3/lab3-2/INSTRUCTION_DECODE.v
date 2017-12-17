`timescale 1ns/1ps

module INSTRUCTION_DECODE(
	clk, rst,
	PC, IR,
	MW_ALUout,
	MW_RD,
    MW_RegWrite,

    DX_PC,
	RD,
	A, B, Imm, JAddr,
	ALUCtr,
    ALUSrc,
    lhWrite, lhRead, mflh,
    Jump,
    Branch,
    DX_MemWrite, DX_MemToReg, DX_RegWrite
);

input       clk,rst;
input       [31:0] PC, IR, MW_ALUout;
input       [4:0] MW_RD;
input       MW_RegWrite;
output reg  [31:0] DX_PC;
output reg  [4:0] RD;
output reg  [31:0] A, B, Imm, JAddr;
output reg  [2:0] ALUCtr;
output reg  ALUSrc;
output reg  lhWrite, lhRead, mflh;
output reg  Jump;
output reg  Branch;
output reg  DX_MemWrite, DX_MemToReg, DX_RegWrite;
reg         [31:0] REG [0:31];

//Write back
always @(posedge clk)//add new Dst REG source here
	if(MW_RD && MW_RegWrite)
	  REG[MW_RD] <= MW_ALUout;
	else
	  REG[MW_RD] <= REG[MW_RD];//keep REG[0] always equal zero

//set A, and other register content(j/beq flag and address)
always @(posedge clk or posedge rst) begin
    if(rst) begin
        DX_PC   <= 32'b0;
        A 	    <= 32'b0;
        B 	    <= 32'b0;
        Imm	    <= 32'b0;
        JAddr 	<= 32'b0;
    end
    else begin
        DX_PC   <= PC;
        A    	<= REG[IR[25:21]];
        B   	<= REG[IR[20:16]];
        Imm     <= {{16{IR[15]}}, IR[15:0]};
        JAddr   <= {PC[31:28], IR[25:0], 2'b0};
    end
end

//set control signal, choose Dst REG, and set B
always @(posedge clk or posedge rst) begin
    if (rst) begin
        ALUCtr      <= 3'b0;
        Jump        <= 1'b0;
        Branch      <= 1'b0;
        DX_MemWrite <= 1'b0;
        DX_MemToReg <= 1'b0;
        DX_RegWrite <= 1'b0;
        RD 	        <= 5'b0;
    end
    else begin
        ALUSrc      <= (IR[31:29] != 3'b000)?               1: 0;
        Jump        <= (IR[31:27] == 5'b00001)?             1: 0;
        Branch      <= (IR[31:28] == 4'b0001)?              1: 0;
        DX_MemToReg <= (IR[31:29] == 3'b100)?               1: 0;
        DX_MemWrite <= (IR[31:29] == 3'b101)?               1: 0;
        lhWrite     <= ({IR[31:26],IR[5:2]} == 10'b110)?    1: 0;
        lhRead      <= ({IR[31:26],IR[5:2]} == 10'b110)?    1: 0;
        RD          <= (IR[31:26] == 6'b0)? IR[15:11]: IR[20:16];
        DX_RegWrite <= (IR[31:26]==6'b0 || IR[31:29]==3'b001 || IR[31:29]==3'b100)? 1: 0;
        mflh        <= IR[1];
        case (IR[31:26])
            6'b000000: begin // R-Type
                case (IR[5:0])
                    //6'b010000: // mfhi
                    //6'b010010: // mflo
                    //6'b011000: // mult
                    //6'b011010: // div
                    6'b100000: ALUCtr <= 3'b010; // add
                    6'b100010: ALUCtr <= 3'b110; // sub
                    6'b100100: ALUCtr <= 3'b000; // and
                    6'b100101: ALUCtr <= 3'b001; // or
                    6'b101010: ALUCtr <= 3'b111; // slt
                endcase
            end
            // 000010: j
            // 000100: beq
            // 000110: blez
            6'b001000: ALUCtr <= 3'b010; // addi
            6'b100011: ALUCtr <= 3'b010; // lw
            6'b101011: ALUCtr <= 3'b010; // sw
        endcase
    end
end

endmodule
