`timescale 1ns/1ps
`include "maxmin.v"
module tb;
    reg clk, rst;
    reg signed [15:0] din;
    wire [15:0] dout;
    integer i;
    maxmin mm1(clk, rst, din, dout, rdy);
    initial begin
        $dumpfile("maxmin.vcd");
        $dumpvars;
        clk = 0;
        rst = 0;
        din = 0;
        #10 rst = 1;
        for (i=1; i<=16; i++) begin
            din = i * (-1)**i;
            #20;
        end
        #500 $finish;
    end
    always #10 clk = ~clk;
endmodule
