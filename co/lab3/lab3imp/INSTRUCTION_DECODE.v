`timescale 1ns/1ps

module INSTRUCTION_DECODE(
    clk,
    rst,
    IR,
    PC,
    MW_RD,
    MW_ALUout,
    MW_CTRL,

    A,
    B,
    C,
    RD,
    ALUctr,
    CTRL
);

input clk,rst;
input [31:0]IR, PC, MW_ALUout;
input [4:0] MW_RD;
input [5:0] MW_CTRL;

output reg [31:0] A, B, C;
output reg [4:0] RD;
output reg [2:0] ALUctr;
output reg [5:0] CTRL;

//register file
reg [31:0] REG [0:31];

//Write back
always @(posedge clk)//add new Dst REG source here
    if(MW_RD)
        REG[MW_RD] <= MW_ALUout;
    else
        REG[MW_RD] <= REG[MW_RD];//keep REG[0] always equal zero

    //set A, and other register content(j/beq flag and address)	
    always @(posedge clk or posedge rst) begin
        if(rst) begin
            A 	<=32'b0;
            CTRL <= 6'b0;
        end 
        else begin
            A 	<=REG[IR[25:21]];
            CTRL <= IR[31:26];
        end
    end

    //set control signal, choose Dst REG, and set B	
    always @(posedge clk or posedge rst) begin
        if(rst) begin
            B 		<=32'b0;
            C 		<=32'b0;
            RD 		<=5'b0;
            ALUctr 	<=3'b0;
        end 
        else begin
            case(IR[31:26])
                6'd0://R-Type
                begin
                    C <= 32'd0;
                    case(IR[5:0])//funct & setting ALUctr
                        6'd32://add
                        begin
                            B	<=REG[IR[20:16]];
                            RD	<=IR[15:11];
                            ALUctr <=3'b010;//self define ALUctr value
                        end
                        6'd34://sub
                        begin
                            //define sub behavior here
                            B	<=REG[IR[20:16]];
                            RD	<=IR[15:11];
                            ALUctr <=3'b110;//self define ALUctr value
                        end
                        6'b100100://and
                        begin
                            //define sub behavior here
                            B	<=REG[IR[20:16]];
                            RD	<=IR[15:11];
                            ALUctr <=3'b000;//self define ALUctr value
                        end
                        6'b100101://or
                        begin
                            //define sub behavior here
                            B	<=REG[IR[20:16]];
                            RD	<=IR[15:11];
                            ALUctr <=3'b001;//self define ALUctr value
                        end
                        6'd42://slt
                        begin
                            //define slt behavior here
                            B	<=REG[IR[20:16]];
                            RD	<=IR[15:11];
                            ALUctr <=3'b111;//self define ALUctr value
                        end
                    endcase
                end
                6'd35://lw
                begin
                    //define lw behavior here
                    B   <= {16'b0,IR[15:0]};
                    RD  <= IR[20:16];
                    ALUctr <= 3'b010;
                end
                6'd43://sw
                begin
                    //define sw behavior here
                    B   <= {16'b0,IR[15:0]};
                    RD  <= IR[20:16];
                    ALUctr <= 3'b010;
                end
                6'd4://beq
                begin
                    //define beq behavior here
                end
                6'd2://j
                begin
                    //define j behavior here
                end
            endcase
        end
    end
endmodule
