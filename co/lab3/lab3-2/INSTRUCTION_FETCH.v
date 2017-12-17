`timescale 1ns/1ps

module INSTRUCTION_FETCH(
	clk, rst,
    Jump, Branch,
    JAddr, BAddr,

	PC, IR
);

input clk, rst;
input Jump, Branch;
input [31:0] JAddr, BAddr;
output reg 	[31:0] PC, IR;

//instruction memory
reg [31:0] instruction [127:0];

// output program counter and instruction
always @(posedge clk or posedge rst) begin
    if (rst) begin
		PC <= 32'd0;
		IR <= 32'd0;
    end
    else begin
        PC <= (Jump)? JAddr: (Branch)? BAddr: PC+4;
		IR <= instruction[PC[10:2]];
    end
end

endmodule
