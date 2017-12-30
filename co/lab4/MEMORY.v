`timescale 1ns/1ps

module MEMORY(
	clk, rst,
    XM_MemWrite, XM_MemToReg, XM_RegWrite,
	XM_RD,
	XM_B, ALUout,
	input_number,

    MW_RegWrite,
	MW_RD,
	MW_ALUout
);

input       clk, rst;
input       XM_MemWrite, XM_MemToReg, XM_RegWrite;
input       [4:0] XM_RD;
input       [31:0] XM_B, ALUout;
input       [31:0] input_number;
output reg  MW_RegWrite;
output reg  [4:0] MW_RD;
output reg  [31:0] MW_ALUout;
reg         [31:0] DM [0:127];

//send to Dst REG: "load word from data memory" or  "ALUout"
always @(posedge clk) begin
    if(rst) begin
        MW_RD		<= 5'b0;
        MW_ALUout	<= 32'b0;
        MW_RegWrite <= 0;
        DM[0]       <= input_number;
    end
    else begin
        MW_RD   		<= XM_RD;
        MW_ALUout   	<= (XM_MemToReg)? DM[ALUout[6:0]]: ALUout;
        DM[ALUout[6:0]] <= (XM_MemWrite)? XM_B: DM[ALUout[6:0]];
        MW_RegWrite     <= XM_RegWrite;
    end
end

endmodule
