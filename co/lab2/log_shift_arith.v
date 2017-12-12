module log_shift_arith(din, shamt, dout);
 input signed[15:0]din;
 input [3:0]shamt;
 output [15:0]dout;
 wire [15:0] t1,t2,t3,t4;
 assign t1 = (shamt[3])?{{8{din[15]}},din[15:8]}:din;
 assign t2 = (shamt[2])?{{4{t1[15]}},t1[15:4]}:t1;
 assign t3 = (shamt[1])?{{2{t2[15]}},t2[15:2]}:t2;
 assign t4 = (shamt[0])?{{1{t3[15]}},t3[15:1]}:t3;

 assign	dout = t4;

endmodule