`timescale 1ns/1ps

module MEMORY(
    clk,
    rst,
    ALUout,
    XM_RD,
    XM_B,
    XM_CTRL,

    MW_ALUout,
    MW_RD,
    MW_CTRL
);
input clk, rst;
input [31:0] ALUout;
input [4:0] XM_RD;
input [31:0] XM_B;
input [5:0] XM_CTRL;

output reg [31:0] MW_ALUout;
output reg [4:0] MW_RD;
output reg [5:0] MW_CTRL;

//data memory
reg [31:0] DM [0:127];
/*
//always store word to data memory
always @(posedge clk)
    if(XM_MemWrite)
        DM[ALUout[6:0]] <= XM_MD;
    */

   //send to Dst REG: "load word from data memory" or  "ALUout"
   always @(posedge clk) begin
       if(rst) begin
           MW_ALUout	<=	32'b0;
           MW_RD		<=	5'b0;
           MW_CTRL      <= 5'd0;
       end
       else begin
           case (XM_CTRL)
               6'd35:
               begin
                   MW_ALUout <= DM[ALUout];
                   MW_RD <= XM_RD;
               end
               6'd43:
               begin
                   DM[ALUout] <= XM_B;
                   MW_RD <= 5'b0;
               end
               6'd0:
               begin
                   MW_ALUout	<=	ALUout;
                   MW_RD		<=	XM_RD;
               end
           endcase
       end
   end

endmodule
