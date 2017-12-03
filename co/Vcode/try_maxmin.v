module maxmin(clk,rst,din,dout,rdy);

	input clk,rst;
	input signed[15:0]din;
	output rdy;
	output signed[15:0]dout;

	reg rdy;
	reg signed [15:0]dout;
	reg signed [15:0]ar[15:0];
    reg signed [15:0]tmp;
	//reg signed [15:0]min;
	reg [4:0] cnt;
    reg [4:0] i;

	always @(posedge clk or negedge rst)
	 if(~rst) begin
		 rdy=0;
		 dout=0;
		 cnt=0;
         for (i=0; i<16; i++)
             ar[i] = 0;
	 end
	 else if (rdy == 1) begin
         dout = ar[cnt];
         cnt++;
     end
     else if (cnt == 16) begin
         cnt = 0;
         rdy = 1;
     end
     else begin
         tmp = din;
         {tmp,ar[0]} = (cnt<=0)? {tmp,tmp}: (tmp<ar[0])? {ar[0],tmp}: {tmp,ar[0]};
         {tmp,ar[1]} = (cnt<=1)? {tmp,tmp}: (tmp<ar[1])? {ar[1],tmp}: {tmp,ar[1]};
         {tmp,ar[2]} = (cnt<=2)? {tmp,tmp}: (tmp<ar[2])? {ar[2],tmp}: {tmp,ar[2]};
         {tmp,ar[3]} = (cnt<=3)? {tmp,tmp}: (tmp<ar[3])? {ar[3],tmp}: {tmp,ar[3]};
         {tmp,ar[4]} = (cnt<=4)? {tmp,tmp}: (tmp<ar[4])? {ar[4],tmp}: {tmp,ar[4]};
         {tmp,ar[5]} = (cnt<=5)? {tmp,tmp}: (tmp<ar[5])? {ar[5],tmp}: {tmp,ar[5]};
         {tmp,ar[6]} = (cnt<=6)? {tmp,tmp}: (tmp<ar[6])? {ar[6],tmp}: {tmp,ar[6]};
         {tmp,ar[7]} = (cnt<=7)? {tmp,tmp}: (tmp<ar[7])? {ar[7],tmp}: {tmp,ar[7]};
         {tmp,ar[8]} = (cnt<=8)? {tmp,tmp}: (tmp<ar[8])? {ar[8],tmp}: {tmp,ar[8]};
         {tmp,ar[9]} = (cnt<=9)? {tmp,tmp}: (tmp<ar[9])? {ar[9],tmp}: {tmp,ar[9]};
         {tmp,ar[10]} = (cnt<=10)? {tmp,tmp}: (tmp<ar[10])? {ar[10],tmp}: {tmp,ar[10]};
         {tmp,ar[11]} = (cnt<=11)? {tmp,tmp}: (tmp<ar[11])? {ar[11],tmp}: {tmp,ar[11]};
         {tmp,ar[12]} = (cnt<=12)? {tmp,tmp}: (tmp<ar[12])? {ar[12],tmp}: {tmp,ar[12]};
         {tmp,ar[13]} = (cnt<=13)? {tmp,tmp}: (tmp<ar[13])? {ar[13],tmp}: {tmp,ar[13]};
         {tmp,ar[14]} = (cnt<=14)? {tmp,tmp}: (tmp<ar[14])? {ar[14],tmp}: {tmp,ar[14]};
         {tmp,ar[15]} = (cnt<=15)? {tmp,tmp}: (tmp<ar[15])? {ar[15],tmp}: {tmp,ar[15]};
         cnt += 1;
	 end
endmodule
