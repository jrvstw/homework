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
    if(rst) begin
        ALUCtr      <= 3'b0;
        Jump        <= 1'b0;
        Branch      <= 1'b0;
        DX_MemWrite <= 1'b0;
        DX_MemToReg <= 1'b0;
        DX_RegWrite <= 1'b0;
        RD 	        <= 5'b0;
    end
    else case (IR[31:26])
        6'b0: begin // R-Type
            ALUSrc      <= 1'b0;
            Jump        <= 1'b0;
            Branch      <= 1'b0;
            DX_MemWrite <= 1'b0;
            DX_MemToReg <= 1'b0;
            DX_RegWrite <= 1'b1;
            RD          <= IR[15:11];
            case (IR[5:0])
                6'b100000: ALUCtr <= 3'b010; // add
                6'b100010: ALUCtr <= 3'b110; // sub
                6'b100100: ALUCtr <= 3'b000; // and
                6'b100101: ALUCtr <= 3'b001; // or
                6'b101010: ALUCtr <= 3'b111; // slt
            endcase
        end
        6'b000010: begin // j
            Jump        <= 1;
            Branch      <= 0;
            DX_MemWrite <= 1'b0;
            DX_MemToReg <= 1'b0;
        end
        6'b000100: begin // beq
            ALUSrc      <= 1'b0;
            ALUCtr      <= 3'b110;
            Jump        <= 0;
            Branch      <= 1;
            DX_MemWrite <= 1'b0;
            DX_MemToReg <= 1'b0;
            DX_RegWrite <= 0;
            RD          <= IR[20:16];
        end
        6'b001000: begin // addi
            ALUSrc      <= 1'b1;
            ALUCtr      <= 3'b010;
            Jump        <= 1'b0;
            Branch      <= 1'b0;
            DX_MemWrite <= 1'b0;
            DX_MemToReg <= 1'b0;
            DX_RegWrite <= 1'b1;
            RD          <= IR[20:16];
        end
        6'b100011: begin // lw
            ALUSrc      <= 1'b1;
            ALUCtr      <= 3'b010;
            Jump        <= 1'b0;
            Branch      <= 1'b0;
            DX_MemWrite <= 1'b0;
            DX_MemToReg <= 1'b1;
            DX_RegWrite <= 1'b1;
            RD          <= IR[20:16];
        end
        6'b101011: begin // sw
            ALUSrc      <= 1'b1;
            ALUCtr      <= 3'b010;
            Jump        <= 1'b0;
            Branch      <= 1'b0;
            DX_MemWrite <= 1'b1;
            DX_MemToReg <= 1'b0;
            DX_RegWrite <= 1'b0;
            RD          <= IR[20:16];
        end
    endcase
end

endmodule
