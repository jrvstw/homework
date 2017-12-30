`define CYCLE_TIME 20
//`define INSTRUCTION_NUMBERS 2000
`define TEST_NUMBER 14
`timescale 1ns/1ps
`include "CPU.v"

module testbench;
reg Clk, Rst;
reg [31:0] cycles, i;


// Instruction DM initialilation
initial begin
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
end


// Data Memory & Register Files initialilation
initial begin
	for (i=0; i<128; i=i+1)
        cpu.MEM.DM[i] = 32'b0;
	cpu.MEM.DM[0] = 32'd`TEST_NUMBER;

	for (i=0; i<32; i=i+1)
        cpu.ID.REG[i] = 32'b0;

end


//clock cycle time is 20ns, inverse Clk value per 10ns
initial Clk = 1'b1;
always #(`CYCLE_TIME/2) Clk = ~Clk;


//Rst signal
initial begin
	cycles = 32'b0;
	Rst = 1'b1;
	#12 Rst = 1'b0;
end


CPU cpu( .clk(Clk), .rst(Rst));


//display all Register value and Data memory content
always @(posedge Clk) begin
	cycles <= cycles + 1;
    if (cpu.MEM.DM[2]) begin
        $display("PC: %d    cycles: %d", cpu.FD_PC>>2 , cycles);
        $display("\n    DM[0]    DM[1]    DM[2]");
        $display(" %8d %8d %8d", cpu.MEM.DM[0],cpu.MEM.DM[1],cpu.MEM.DM[2]);
        $finish;
    end
    $display("PC: %d cycles: %d", cpu.FD_PC>>2 , cycles);
    $display("  R00-R07: %08x %08x %08x %08x %08x %08x %08x %08x", cpu.ID.REG[0], cpu.ID.REG[1], cpu.ID.REG[2], cpu.ID.REG[3],cpu.ID.REG[4], cpu.ID.REG[5], cpu.ID.REG[6], cpu.ID.REG[7]);
    $display("  R08-R15: %08x %08x %08x %08x %08x %08x %08x %08x", cpu.ID.REG[8], cpu.ID.REG[9], cpu.ID.REG[10], cpu.ID.REG[11],cpu.ID.REG[12], cpu.ID.REG[13], cpu.ID.REG[14], cpu.ID.REG[15]);
    $display("  R16-R23: %08x %08x %08x %08x %08x %08x %08x %08x", cpu.ID.REG[16], cpu.ID.REG[17], cpu.ID.REG[18], cpu.ID.REG[19],cpu.ID.REG[20], cpu.ID.REG[21], cpu.ID.REG[22], cpu.ID.REG[23]);
    $display("  R24-R31: %08x %08x %08x %08x %08x %08x %08x %08x", cpu.ID.REG[24], cpu.ID.REG[25], cpu.ID.REG[26], cpu.ID.REG[27],cpu.ID.REG[28], cpu.ID.REG[29], cpu.ID.REG[30], cpu.ID.REG[31]);
    $display("  0x00   : %08x %08x %08x %08x %08x %08x %08x %08x", cpu.MEM.DM[0],cpu.MEM.DM[1],cpu.MEM.DM[2],cpu.MEM.DM[3],cpu.MEM.DM[4],cpu.MEM.DM[5],cpu.MEM.DM[6],cpu.MEM.DM[7]);
    $display("  0x08   : %08x %08x %08x %08x %08x %08x %08x %08x", cpu.MEM.DM[8],cpu.MEM.DM[9],cpu.MEM.DM[10],cpu.MEM.DM[11],cpu.MEM.DM[12],cpu.MEM.DM[13],cpu.MEM.DM[14],cpu.MEM.DM[15]);
    $display("  LO, HI : %08x %08x", cpu.EXE.LO, cpu.EXE.HI);
    if (cpu.MEM.DM[2]) $finish;
end


//generate wave file, it can use gtkwave to display
initial begin
	$dumpfile("cpu_hw.vcd");
	$dumpvars;
end
endmodule

