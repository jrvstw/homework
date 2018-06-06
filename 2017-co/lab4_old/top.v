`timescale 1ns / 1ps
`include "CPU.v"
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/18 13:20:44
// Design Name: 
// Module Name: top
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module top(
    input clk, 
    input rst,
    input sw0,
    input sw1,
    input sw2,
    input sw3,
    input sw4,
    input sw5,
    input sw6,
    input sw7,
    input sw8,
	input sw9,
    input sw10,
    input sw11,
    input sw12,

    output a,
    output b,
    output c,
    output d,
    output e,
    output f,
    output g,
    output dp,
    output d0,
    output d1,
    output d2,
    output d3,
    output d4,
    output d5,
    output d6,
    output d7 
    );
reg [17:0] counter;
reg [2:0] state;
reg [6:0] seg_number,seg_data;
reg [7:0] scan;

reg [12:0] input_number, first_number, second_number;
reg [31:0] i;

initial begin
    // Instruction DM initialilation
    cpu.IF.PC = 0;
    for (i=0; i<128; i=i+1)
        cpu.IF.instruction[i] = 32'b100000; // NOP(add $0, $0, $0)
    cpu.IF.instruction[ 0] = 32'b100011_00000_01000_00000_00000_000000;	//      lw      $8, 0($0)
    cpu.IF.instruction[ 4] = 32'b001000_01000_01000_00000_00000_000001;	//incr: addi    $8, $8, 1
    cpu.IF.instruction[ 5] = 32'b001000_00000_01001_00000_00000_000010;	//      addi    $9, $0, 2
    cpu.IF.instruction[ 9] = 32'b000000_01000_01001_00000_00000_011010;	//chec: div     $8, $9
    cpu.IF.instruction[10] = 32'b000000_00000_00000_01010_00000_010000;	//      mfhi    $10
    cpu.IF.instruction[14] = 32'b000100_01010_00000_11111_11111_110101;	//      beq     $10, $0, incr: (-11)
    cpu.IF.instruction[11] = 32'b001000_01001_01001_00000_00000_000001;	//      addi    $9, $9, 1
    cpu.IF.instruction[15] = 32'b000000_01001_01001_00000_00000_011000;	//      mult    $9, $9
    cpu.IF.instruction[16] = 32'b000000_00000_00000_01011_00000_010010;	//      mflo    $11
    cpu.IF.instruction[20] = 32'b000000_01000_01011_00001_00000_101010;	//      slt     $1, $8, $11
    cpu.IF.instruction[24] = 32'b000100_00001_00000_11111_11111_110000;	//      beq     $1, $0, chec: (-16)
    cpu.IF.instruction[28] = 32'b101011_00000_01000_00000_00000_000001;	//      sw      $8, 1($0)

    cpu.IF.instruction[ 1] = 32'b100011_00000_01100_00000_00000_000000;	//      lw      $12, 0($0)
    cpu.IF.instruction[29] = 32'b001000_01100_01100_11111_11111_111111;	//incr: addi    $12, $12, -1
    cpu.IF.instruction[30] = 32'b001000_00000_01101_00000_00000_000010;	//      addi    $13, $0, 2
    cpu.IF.instruction[34] = 32'b000000_01100_01101_00000_00000_011010;	//chec: div     $12, $13
    cpu.IF.instruction[35] = 32'b000000_00000_00000_01110_00000_010000;	//      mfhi    $14
    cpu.IF.instruction[39] = 32'b000100_01110_00000_11111_11111_110101;	//      beq     $14, $0, incr: (-11)
    cpu.IF.instruction[36] = 32'b001000_01101_01101_00000_00000_000001;	//      addi    $13, $13, 1
    cpu.IF.instruction[40] = 32'b000000_01101_01101_00000_00000_011000;	//      mult    $13, $13
    cpu.IF.instruction[41] = 32'b000000_00000_00000_01111_00000_010010;	//      mflo    $15
    cpu.IF.instruction[45] = 32'b000000_01100_01111_00001_00000_101010;	//      slt     $1, $12, $15
    cpu.IF.instruction[49] = 32'b000100_00001_00000_11111_11111_110000;	//      beq     $1, $0, chec: (-16)
    cpu.IF.instruction[53] = 32'b101011_00000_01100_00000_00000_000010;	//      sw      $12, 2($0)

// Data Memory & Register Files initialilation
	for (i=0; i<128; i=i+1)
        cpu.MEM.DM[i] = 32'b0;

	for (i=0; i<32; i=i+1)
        cpu.ID.REG[i] = 32'b0;

end

//wtite down your code here
always@(posedge clk)begin
    cpu.MEM.DM[0]   <= {19'b0, sw12, sw11, sw10, sw9, sw8, sw7, sw6, sw5, sw4, sw3, sw2, sw1, sw0};
end

always @(negedge rst) begin
    first_number    <= cpu.MEM.DM[1][12:0];
    second_number   <= cpu.MEM.DM[2][12:0];
end

//8Áû(d0~d7)7-segment(a~g)Åã¥Ü dp¬°¥k¤U¨¤ªº.
assign {d7,d6,d5,d4,d3,d2,d1,d0} = scan;
assign dp = ((state==1) || (state==3)) ? 0 : 1;  //1,3 light_on
always@(posedge clk) begin
  counter <=(counter<=100000) ? (counter +1) : 0;
  state <= (counter==100000) ? (state + 1) : state;
   case(state)
	0:begin
	  seg_number <= first_number/1000;//6­Óswitch­È³Ì¦h¬°63,63/10=6,Åã¥Ü¦b¥ªÃä
	  scan <= 8'b0111_1111;
	end
	1:begin
	  seg_number <= (first_number%1000)/100;//63%10=3,Åã¥Ü¦b¥kÃä
	  scan <= 8'b1011_1111;
	end
	2:begin
	  seg_number <= (first_number%100)/10;
	  scan <= 8'b1101_1111;
	end
	3:begin
	  seg_number <= first_number%10;
	  scan <= 8'b1110_1111;
	end
	4:begin
	  seg_number <= second_number/1000;//63*63=3969,3969/1000=3
	  scan <= 8'b1111_0111;
	end
	5:begin
	  seg_number <= (second_number%1000)/100;//3969%1000=969,969/1000=9
	  scan <= 8'b1111_1011;
	end
	6:begin
	  seg_number <= (second_number%100)/10;
	  scan <= 8'b1111_1101;
	end
	7:begin
	  seg_number <= second_number%10;
	  scan <= 8'b1111_1110;
	end
	default: state <= state;
  endcase 
end  

//7-segment ¿é¥X¼Æ¦r¸Ñ½X
assign {g,f,e,d,c,b,a} = seg_data;
always@(posedge clk) begin  
  case(seg_number)
	16'd0:seg_data <= 7'b100_0000;
	16'd1:seg_data <= 7'b111_1001;
	16'd2:seg_data <= 7'b010_0100;
	16'd3:seg_data <= 7'b011_0000;
	16'd4:seg_data <= 7'b001_1001;
	16'd5:seg_data <= 7'b001_0010;
	16'd6:seg_data <= 7'b000_0010;
	16'd7:seg_data <= 7'b101_1000;
	16'd8:seg_data <= 7'b000_0000;
	16'd9:seg_data <= 7'b001_0000;
	default: seg_number <= seg_number;
  endcase
end 
endmodule
