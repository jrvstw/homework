module acc(din,dout,clk,rst,en);

 input clk,rst,en;
 input [15:0]din;
 output[15:0]dout;
 reg[15:0]dout;
 
 always @(posedge clk or negedge rst)
	if(~rst) dout = 0;
	
	else if(en) dout += din;
	
	else dout = dout;
	
endmodule
	