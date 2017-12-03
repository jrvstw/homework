`timescale 1ns/1ps

module logshift(din, shamt, dout);
    input [31:0] din;
    input [4:0] shamt;
    output [31:0] dout;
    wire [31:0] dout;
    wire [31:0] t4, t3, t2, t1;

    assign t4 = (shamt[4])? {{16{din[31]}},din[31:16]}: din[31:0];
    assign t3 = (shamt[3])? {{8{t4[31]}},t4[31:8]}: t4[31:0];
    assign t2 = (shamt[2])? {{4{t3[31]}},t3[31:4]}: t3[31:0];
    assign t1 = (shamt[1])? {{2{t2[31]}},t2[31:2]}: t2[31:0];
    assign dout = (shamt[0])? {t1[31],t1[31:1]}: t1[31:0];
endmodule

module tb_logshift;
    reg [31:0] din;
    reg [4:0] shamt;
    wire [31:0] dout;
    logshift ls1(din, shamt, dout);
    initial begin
        $dumpfile("examlog.vcd");
        $dumpvars;
        din = 0;
        shamt = 0;
        #10
        din = 1024;
        shamt = 1;
        #10
        shamt = 5;
        #10
        shamt = 11;
        #10
        din = -1024;
        shamt = 1;
        #10
        shamt = 5;
        #10
        shamt = 11;
        #10 $finish;
    end
endmodule


