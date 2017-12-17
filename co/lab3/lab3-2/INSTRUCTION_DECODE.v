`timescale 1ns/1ps

module INSTRUCTION_DECODE(
	clk,
	rst,
	IR,
	PC,
	MW_RD,
	MW_ALUout,
    MW_RegWrite,

	A,
	B,
	RD,
	ALUctr,
    Jump,
    JAddr,
    Branch,
    DX_RegWrite
);

input clk,rst;
input [31:0]IR, PC, MW_ALUout;
input [4:0] MW_RD;
input MW_RegWrite;

output reg [31:0] A, B;
output reg [4:0] RD;
output reg [2:0] ALUctr;
output reg Jump;
output reg [31:0] JAddr;
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
        A 	<=32'b0;
    end 
    else begin
        A 	<=REG[IR[25:21]];
    end
end

//set control signal, choose Dst REG, and set B	
always @(posedge clk or posedge rst) begin
    if(rst) begin
        B 		<=32'b0;
        RD 		<=5'b0;
        ALUctr 	<=3'b0;
    end 
    else begin
        case(IR[31:26])
            6'd0://R-Type
            begin
                DX_RegWrite <= 1;
                Jump <= 0;
                case(IR[5:0])//funct & setting ALUctr
                    6'd32://add
                    begin
                        B	<=REG[IR[20:16]];
                        RD	<=IR[15:11];
                        ALUctr <=3'b010;//self define ALUctr value
                    end
                    6'd34://sub
                    begin
                        B	<=REG[IR[20:16]];
                        RD	<=IR[15:11];
                        ALUctr <=3'b110;//self define ALUctr value
                    end
                    6'b100100: // and
                    begin
                        B	<=REG[IR[20:16]];
                        RD	<=IR[15:11];
                        ALUctr <=3'b000;//self define ALUctr value
                    end
                    6'b100101: // or
                    begin
                        B	<=REG[IR[20:16]];
                        RD	<=IR[15:11];
                        ALUctr <=3'b001;//self define ALUctr value
                    end
                    6'd42://slt
                    begin
                        B	<=REG[IR[20:16]];
                        RD	<=IR[15:11];
                        ALUctr <= 3'b111;
                    end
                endcase
            end
            6'd35://lw
            begin
                Jump <= 0;
                Branch <= 0;
                DX_RegWrite <= 1;
            end
            6'd43://sw
            begin
                Jump <= 0;
                Branch <= 0;
                DX_RegWrite <= 0;
            end
            6'd4://beq
            begin
                Jump <= 0;
                Branch <= 1;
                DX_RegWrite <= 0;
            end
            6'd2://j
            begin
                Jump <= 1;
                JAddr <= {PC[31:28],IR[25:0],2'b0};
                Branch <= 0;
            end
        endcase
    end
end
endmodule
