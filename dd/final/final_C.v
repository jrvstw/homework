`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:  ECL408
// Engineer: CHIAO-CHUAN HUANG
// 
// Create Date:    14:45:51 05/04/2016 
// Design Name:    NEXYS4 peripheral
// Module Name:    top 
// Project Name:   DDLab 9
// Target Devices: NEXYS4 DDR
// Tool versions:  ISE Design Suite 14.2
// Description: Use 8 switches to control 8 7-segment light. 
//
// Dependencies: 
//
// Revision: version 1
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module top(
	 input clk,
	 input btnc,
	 input btnl,
	 input btnr,
	 
	 output led0, 
	 output led1, 
	 output led2, 
    output led3, 
	 output led4, 
	 output led5, 
	 output led6, 
	 output led7,
	 output led8,
	 output led9,
	 output led10,
	 output led11,
	 output led12,
	 output led13,
	 output led14,
	 output led15
    );
reg [1:0] state;
reg [31:0] cnt;
reg [15:0] result;


always@(posedge clk)begin
	cnt <= (cnt<=32'd10000000)? (cnt+32'd1): 32'd0;

	if (btnc) begin
		state <= 2'd0;
		result <= 16'b0;
	end
	else if (btnl) begin
		state <= 2'd1;
		result <= 16'b1;
	end
	else if (btnr) begin
		state <=2'd2;
		result <= 16'b1000_0000_0000_0000;
	end
	else begin
		state <= state;
		result <= result;
	end
	
	if (cnt==32'd0) begin
		if (state==2'd1) begin
			if (result==16'b1000_0000_0000_0000)
				result <= 16'b1;
			else
				result <= (result<<1'b1);		
		end
		
		else if (state==2'd2) begin
			if (result==16'b1)
				result <= 16'b1000_0000_0000_0000;
			else
				result <= (result>>1'b1);
		end
		
		else
			result <= result;
	end
	
	
end

assign {led15,led14,led13,led12,led11,led10,led9,led8,led7,led6,led5,led4,led3,led2,led1,led0} = result;

endmodule
