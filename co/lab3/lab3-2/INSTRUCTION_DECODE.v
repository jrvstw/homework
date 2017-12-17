`timescale 1ns/1ps

module INSTRUCTION_DECODE(
	clk,
	rst,
	IR,
	PC,
	MW_RD,
	MW_ALUout,
    MW_RegWrite,

	A, B, Imm, JAddr,
	RD,
	ALUctr,
    ALUSrc,
    Jump,
    Branch,
    DX_RegWrite
);

input clk,rst;
input [31:0]IR, PC, MW_ALUout;
input [4:0] MW_RD;
input MW_RegWrite;

output reg [31:0] A, B, Imm, JAddr;
output reg [4:0] RD;
output reg [2:0] ALUctr;
output reg ALUSrc;
output reg Jump;
output reg Branch;
output reg DX_RegWrite;

//register file
reg [31:0] REG [0:31];

//Write back
always @(posedge clk)//add new Dst REG source here
	if(MW_RD && MW_RegWrite)
	  REG[MW_RD] <= MW_ALUout;
	else
	  REG[MW_RD] <= REG[MW_RD];//keep REG[0] always equal zero

//set A, and other register content(j/beq flag and address)	
always @(posedge clk or posedge rst) begin
    if(rst) begin
        A 	    <= 32'b0;
        B 	    <= 32'b0;
        Imm	    <= 32'b0;
        JAddr 	<= 32'b0;
    end 
    else begin
        A    	<= REG[IR[25:21]];
        B   	<= REG[IR[20:16]];
        Imm     <= {16'b0, IR[15:0]};
        JAddr   <= {PC[31:28], IR[25:0], 2'b0};
    end
end

//set control signal, choose Dst REG, and set B	
always @(posedge clk or posedge rst) begin
    if(rst) begin
        ALUctr 	<= 3'b0;
        Jump    <= 1'b0;
        Branch  <= 1'b0;
        DX_RegWrite <= 1'b0;
        RD 		<= 5'b0;
    end 
    else begin
        case(IR[31:26])
            6'd0://R-Type
            begin
                ALUSrc      <= 1'b0;
                Jump        <= 1'b0;
                Branch      <= 1'b0;
                DX_RegWrite <= 1'b1;
                RD	<=IR[15:11];
                case(IR[5:0])//funct & setting ALUctr
                    6'b100000: ALUctr <= 3'b010; //add
                    6'b100010: ALUctr <= 3'b110; //sub
                    6'b100100: ALUctr <= 3'b000; // and
                    6'b100101: ALUctr <= 3'b001; // or
                    6'b101010: ALUctr <= 3'b111; //slt
                endcase
            end
            6'b001000: // addi
            begin
                ALUSrc      <= 1'b1;
                ALUctr      <= 3'b010;
                Jump        <= 1'b0;
                Branch      <= 1'b0;
                DX_RegWrite <= 1'b1;
                RD          <= IR[20:16];
            end
            6'd35://lw
            begin
                ALUSrc      <= 1'b1;
                Jump <= 0;
                Branch <= 0;
                DX_RegWrite <= 1;
                RD  <= IR[20:16];
            end
            6'd43://sw
            begin
                ALUSrc      <= 1'b1;
                Jump <= 0;
                Branch <= 0;
                DX_RegWrite <= 0;
                RD  <= IR[20:16];
            end
            6'b000100://beq
            begin
                ALUSrc      <= 1'b1;
                ALUctr      <= 3'b110;
                Jump <= 0;
                Branch <= 1;
                DX_RegWrite <= 1;
                RD <= IR[20:16];
            end
            6'd2://j
            begin
                Jump <= 1;
                Branch <= 0;
            end
        endcase
    end
end
endmodule
