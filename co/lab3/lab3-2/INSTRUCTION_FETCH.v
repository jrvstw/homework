`timescale 1ns/1ps

module INSTRUCTION_FETCH(
	clk,
	rst,
    Jump,
    Branch,
    JAddr,

	PC,
	IR
);

input clk, rst;
input Jump;
input [31:0] JAddr;
input Branch;
output reg 	[31:0] PC, IR;

//instruction memory
reg [31:0] instruction [127:0];

//output instruction
always @(posedge clk or posedge rst) begin
	if(rst)
		IR <= 32'd0;
	else
		IR <= instruction[PC[10:2]];
end

// output program counter
always @(posedge clk or posedge rst) begin
	if(rst)
		PC <= 32'd0;
	else if (Jump)
		PC <= JAddr;
    else if (Branch)
		PC <= PC + 4;
    else
		PC <= PC + 4;
end

endmodule
