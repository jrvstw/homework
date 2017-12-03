module maxmin(clk,rst,din,dout,rdy);

	input clk,rst;
	input signed[15:0]din;
	output rdy;
	output signed[15:0]dout;
	
	reg rdy;
	reg signed [15:0]dout;
	reg signed [15:0]max;
	reg signed [15:0]min;
	reg [4:0] cnt;
	
	always @(posedge clk or negedge rst)
	 if(~rst) begin 
		 rdy=0; 
		 dout=0;
		 cnt=16;
		 max=0;
		 min=0;
	 end
	 
	 else begin
		 max=(max<din)?din:max;
		 min=(min>din)?din:min;
		 cnt -=1;	 
		 if(cnt == 0)begin
			rdy=1;
			dout=min;
		 end
		 else if(rdy==1)
			dout=max;
	 end 
endmodule