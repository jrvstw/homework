module maxmin(clk, rst, din, dout, rdy);
    input clk, rst;
    input signed [15:0] din;
    output signed [15:0] dout;
    output rdy;
    reg signed [15:0] dout;
    reg rdy;

    reg signed [15:0] ar[15:0];
    reg signed [15:0] tmp;
    reg [4:0] cnt;
    reg [4:0]  i;
    always @(posedge clk or negedge rst) begin
        if (~rst) begin
            dout = 0;
            cnt = 0;
            rdy = 0;
            for (i=0; i<16; i++)
                ar[i] = 0;
        end
        else if (rdy) begin
            /*
            dout = (ar[3] + ar[4]) / 2;
            */
            dout = ar[cnt];
            cnt++;
        end
        else if (cnt==16) begin
            rdy = 1;
            cnt = 0;
        end
        else begin
            tmp = din;
            for (i=0; i<16; i++)
                {tmp,ar[i]} = (cnt<=i)? {tmp,tmp}: (tmp<ar[i])? {ar[i],tmp}: {tmp,ar[i]};
            cnt++;
        end
    end
endmodule
