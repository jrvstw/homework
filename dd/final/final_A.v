`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:53:16 05/30/2016 
// Design Name: 
// Module Name:    tri_led 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module tri_led(
	 clk100mhz,
	 btnc,
	 btnl,
	 btnr,
	 btnu,
	 btnd,
	 RGB1_Red,
	 RGB1_Green,
	 RGB1_Blue,
);


input clk100mhz;
input btnc;
input btnl;
input btnr;
input btnu;
input btnd;
output RGB1_Red;
output RGB1_Green;
output RGB1_Blue;
reg [31:0] cnt;   //for 3 stages  (Red, Green, Red) as clk = 100mhz
reg [2:0] phase = 3'd3;
reg [2:0] bright = 3'd1;
reg [2:0] r = 3'd4;
reg [2:0] g = 3'd4;
reg [2:0] b = 3'd4;
reg [31:0] delay;

  clock instance_name
   (// Clock in ports
    .CLK_IN1(clk100mhz),      // IN
    // Clock out ports
    .CLK_OUT1(CLK_OUT1),     // OUT
    .CLK_OUT2(CLK_OUT2),     // OUT
    .CLK_OUT3(CLK_OUT3),     // OUT
    .CLK_OUT4(CLK_OUT4),     // OUT
    .CLK_OUT5(CLK_OUT5),     // OUT
    .CLK_OUT6(CLK_OUT6),     // OUT
    .CLK_OUT7(CLK_OUT7),     // OUT
    // Status and control signals
    .RESET(btnc));       // IN

always@(posedge CLK_OUT3)begin
	delay <= (delay==32'b0)? 32'b0: delay - 32'b1;
	
	if (btnc) begin
		phase <= 3'd3;
		bright <= 3'd1;
		delay <= 32'd50000000;
	end
	
	if (btnl && delay==32'd0 && phase<3'd6) begin
		phase <= phase + 3'd1;
		delay <= 32'd50000000;
	end
	
	if (btnr && delay==32'd0 && phase>3'd0) begin
		phase <= phase - 3'd1;
		delay <= 32'd50000000;
	end
	
	if (btnd && delay==32'd0 && bright>3'd0) begin
		bright <= bright - 3'd1;
		delay <= 32'd50000000;
	end
	
	if (btnu && delay==32'd0 && bright<3'd2) begin
		bright <= bright + 3'd1;
		delay <= 32'd50000000;
	end
	
	case (phase)
	0: begin
		r <= 3'd6 - bright;
		g <= 3'd7;
		b <= 3'd7;
	end
	1: begin
		r <= 3'd6 - bright;
		g <= 3'd7 - bright;
		b <= 3'd7;
	end
	2: begin
		r <= 3'd6 - bright;
		g <= 3'd6 - bright;
		b <= 3'd7;
	end
	3: begin
		r <= 3'd6 - bright;
		g <= 3'd6 - bright;
		b <= 3'd6 - bright;
	end
	4: begin
		r <= 3'd7;
		g <= 3'd6 - bright;
		b <= 3'd7;
	end
	5: begin
		r <= 3'd7;
		g <= 3'd7;
		b <= 3'd6 - bright;
	end
	6: begin
		r <= 3'd6 - bright;
		g <= 3'd7;
		b <= 3'd6 - bright;
	end
	default: begin
		r <= r;
		g <= g;
		b <= b;
	end
	endcase

end



/*****************write down your design below*****************/
assign RGB1_Red 	 = (r==3'd2)? CLK_OUT2: (r==3'd3)? CLK_OUT3: (r==3'd4)? CLK_OUT4: (r==3'd5)? CLK_OUT5: (r==3'd6)? CLK_OUT6: CLK_OUT7;
assign RGB1_Green  = (g==3'd2)? CLK_OUT2: (g==3'd3)? CLK_OUT3: (g==3'd4)? CLK_OUT4: (g==3'd5)? CLK_OUT5: (g==3'd6)? CLK_OUT6: CLK_OUT7;
assign RGB1_Blue 	 = (b==3'd2)? CLK_OUT2: (b==3'd3)? CLK_OUT3: (b==3'd4)? CLK_OUT4: (b==3'd5)? CLK_OUT5: (b==3'd6)? CLK_OUT6: CLK_OUT7;
/*****************write down your design upon *****************/
endmodule
