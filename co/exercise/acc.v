`timescale 1ns/1ps

module aac(clk, rst, en, din, dout);
    input clk, rst, en;
    input signed [15:0] din;
    output signed [15:0] dout;
    reg signed [15:0] dout;
    always @(posedge clk or negedge rst) begin
        if (~rst)
            dout = 0;
        else if (en)
            dout += din;
        else
            dout = dout;
    end
endmodule

module tb_acc;
    reg clk, rst, en;
    reg signed [15:0] din;
    wire [15:0] dout;
    integer i;
    aac tb_acc(clk, rst, en, din, dout);
    initial begin
        $dumpfile("exam.vcd");
        $dumpvars;
        clk = 0;
        rst = 0;
        en = 0;
        #10
        rst = 1;
        en = 1;
        for (i=1; i<=100; i++) begin
            din = i * (-1)**i;
            #20;
        end
        en = 0;
        #100 $finish;
    end
    always #10 clk = ~clk;
endmodule

