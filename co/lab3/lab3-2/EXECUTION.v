`timescale 1ns/1ps

module EXECUTION(
    clk, rst,
    DX_PC,
    DX_RD,
    A, B, Imm,
    ALUctr,
    ALUSrc,
    DX_Branch,
    DX_RegWrite,

    XM_RD,
    ALUout, BAddr,
    XF_Branch,
    XM_RegWrite
);

input clk, rst;
input [31:0] DX_PC;
input [4:0] DX_RD;
input [31:0] A, B, Imm;
input [2:0] ALUctr;
input ALUSrc;
input DX_Branch;
input DX_RegWrite;

output reg [4:0] XM_RD;
output reg [31:0] ALUout, BAddr;
output reg XF_Branch;
output reg XM_RegWrite;

//set pipeline register
always @(posedge clk or posedge rst) begin
    if(rst) begin
        XM_RD       <= 5'd0;
        XF_Branch   <= 1'b0;
        XM_RegWrite <= 1'b0;
        BAddr       <= 1'b0;
    end 
    else begin
        XM_RD       <= DX_RD;
        XF_Branch   <= DX_Branch && (A==B);
        XM_RegWrite <= DX_RegWrite;
        BAddr       <= DX_PC + (Imm<<2);
    end
end

// calculating ALUout
always @(posedge clk or posedge rst) begin
    if(rst) begin
        ALUout	<= 32'd0;
    end 
    else begin
        case(ALUctr)
            3'b010: //add //lw //sw
            begin
                ALUout <= (ALUSrc)? A+Imm: A+B;
            end
            3'b110: //sub
            begin
                ALUout <= (ALUSrc)? A-Imm: A-B;
            end
            3'b000: // and
            begin
                ALUout <= A & B;
            end
            3'b001: // or
            begin
                ALUout <= A | B;
            end
            3'b111: // slt
            begin
                ALUout <= (A < B)? 1: 0;
            end
        endcase
    end
end
endmodule

