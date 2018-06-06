`timescale 1ns/1ps

module INSTRUCTION_FETCH(
	clk, rst,
    Jump, Branch,
    JAddr, BAddr,

	PC, IR
);

input       clk, rst;
input       Jump, Branch;
input       [31:0] JAddr, BAddr;
output reg 	[31:0] PC, IR;
reg         [31:0] instruction [127:0];
reg         [31:0] i;

initial begin
    for (i=0; i<128; i=i+1)
        instruction[i] = 32'b100000; // NOP(add $0, $0, $0)

    instruction[ 0] = 32'b100011_00000_01000_00000_00000_000000;	//      lw      $8, 0($0)
    instruction[ 4] = 32'b001000_01000_01000_00000_00000_000001;	//incr: addi    $8, $8, 1
    instruction[ 5] = 32'b001000_00000_01001_00000_00000_000010;	//      addi    $9, $0, 2
    instruction[ 9] = 32'b000000_01000_01001_00000_00000_011010;	//chec: div     $8, $9
    instruction[10] = 32'b000000_00000_00000_01010_00000_010000;	//      mfhi    $10
    instruction[14] = 32'b000100_01010_00000_11111_11111_110101;	//      beq     $10, $0, incr: (-11)
    instruction[11] = 32'b001000_01001_01001_00000_00000_000001;	//      addi    $9, $9, 1
    instruction[15] = 32'b000000_01001_01001_00000_00000_011000;	//      mult    $9, $9
    instruction[16] = 32'b000000_00000_00000_01011_00000_010010;	//      mflo    $11
    instruction[20] = 32'b000000_01000_01011_00001_00000_101010;	//      slt     $1, $8, $11
    instruction[24] = 32'b000100_00001_00000_11111_11111_110000;	//      beq     $1, $0, chec: (-16)
    instruction[28] = 32'b101011_00000_01000_00000_00000_000001;	//      sw      $8, 1($0)

    instruction[ 1] = 32'b100011_00000_01100_00000_00000_000000;	//      lw      $12, 0($0)
    instruction[29] = 32'b001000_01100_01100_11111_11111_111111;	//incr: addi    $12, $12, -1
    instruction[30] = 32'b001000_00000_01101_00000_00000_000010;	//      addi    $13, $0, 2
    instruction[34] = 32'b000000_01100_01101_00000_00000_011010;	//chec: div     $12, $13
    instruction[35] = 32'b000000_00000_00000_01110_00000_010000;	//      mfhi    $14
    instruction[39] = 32'b000100_01110_00000_11111_11111_110101;	//      beq     $14, $0, incr: (-11)
    instruction[36] = 32'b001000_01101_01101_00000_00000_000001;	//      addi    $13, $13, 1
    instruction[40] = 32'b000000_01101_01101_00000_00000_011000;	//      mult    $13, $13
    instruction[41] = 32'b000000_00000_00000_01111_00000_010010;	//      mflo    $15
    instruction[45] = 32'b000000_01100_01111_00001_00000_101010;	//      slt     $1, $12, $15
    instruction[49] = 32'b000100_00001_00000_11111_11111_110000;	//      beq     $1, $0, chec: (-16)
    instruction[53] = 32'b101011_00000_01100_00000_00000_000010;	//      sw      $12, 2($0)
    
end

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
