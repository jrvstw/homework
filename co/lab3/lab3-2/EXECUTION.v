`timescale 1ns/1ps

module EXECUTION(
    clk, rst,
    DX_PC,
    DX_RD,
    A, B, Imm,
    ALUCtr,
    ALUSrc,
    lhWrite, lhRead, mflh,
    DX_Branch,
    DX_MemWrite, DX_MemToReg, DX_RegWrite,

    XM_RD,
    XM_B, ALUout, BAddr,
    XF_Branch,
    XM_MemWrite, XM_MemToReg, XM_RegWrite
);

input       clk, rst;
input       [31:0] DX_PC;
input       [4:0] DX_RD;
input       [31:0] A, B, Imm;
input       [2:0] ALUCtr;
input       ALUSrc;
input       lhWrite, lhRead, mflh;
input       DX_Branch;
input       DX_MemWrite, DX_MemToReg, DX_RegWrite;
output reg  [4:0] XM_RD;
output reg  [31:0] XM_B, ALUout, BAddr;
output reg  XF_Branch;
output reg  XM_MemWrite, XM_MemToReg, XM_RegWrite;
reg         [31:0] LO, HI;

//set pipeline register
always @(posedge clk or posedge rst) begin
    if(rst) begin
        XM_RD       <= 5'd0;
        XM_B        <= 32'b0;
        XF_Branch   <= 1'b0;
        XM_MemWrite <= 1'b0;
        XM_MemToReg <= 1'b0;
        XM_RegWrite <= 1'b0;
        BAddr       <= 1'b0;
    end
    else begin
        XM_RD       <= DX_RD;
        XM_B        <= B;
        BAddr       <= DX_PC + (Imm<<2);
        XF_Branch   <= DX_Branch && (A==B);
        XM_MemWrite <= DX_MemWrite;
        XM_MemToReg <= DX_MemToReg;
        XM_RegWrite <= DX_RegWrite;
    end
end

// calculating ALUout
always @(posedge clk or posedge rst) begin
    if(rst) begin
        ALUout	<= 32'd0;
    end
    else begin
        case(ALUCtr)
            3'b000: ALUout <= A & B; // and
            3'b001: ALUout <= A | B; // or
            3'b010: ALUout <= (ALUSrc)? A+Imm: A+B; //add //lw //sw
            3'b110: ALUout <= (ALUSrc)? A-Imm: A-B; //sub
            3'b111: ALUout <= (A < B)? 1: 0; // slt
        endcase
    end
end
endmodule

