`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:  ECL408
// Engineer: Shih-Lin Chiu
// 
// Create Date:    14:45:51 05/19/2016 
// Design Name:    V1 Serial multiplier on NEXYS4 thru Verilog
// Module Name:    top 
// Project Name:   DDLab 11
// Target Devices: NEXYS4 DDR
// Tool versions:  ISE Design Suite 14.2
// Description: 1.Use 16 switches to input two numbers 
//              2.Compute the product  
//              3.Use 8 7-segment show the product
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
	 input btnd,
	 input btnl,
	 input btnr,
	 input btnu,

	 output a,
    output b,
    output c,
    output d,
    output e,
    output f,
    output g,
    output dp,
    output d0,
    output d1,
    output d2,
    output d3,
    output d4,
    output d5,
    output d6,
    output d7 
    );

reg [17:0] counter;
reg [2:0] state;
reg [6:0] seg_number,seg_data;
reg [7:0] scan;

reg [1:0] direction;
reg [31:0] cnt;
reg [7:0] result;
reg [6:0] speed = 7'b1000;
reg [31:0] delay;

always@(posedge clk)begin
	cnt <= (cnt<=32'd80000000)? (cnt+speed): 32'd0;
	delay <= (delay==32'b0)? 0: (delay - 32'b1);
	
	if (btnc) begin
		direction <= 2'd0;
		result <= 8'b0;
	end
	
	else if (btnd && speed>7'b1 && delay==32'b0) begin
		speed <= speed >> 1'b1;
		delay <= 32'd50000000;
	end
	
	else if (btnu && speed<7'b100_0000 && delay==32'b0) begin
		speed <= speed << 1'b1;
		delay <= 32'd50000000;
	end
	
	else if (btnl) begin
		direction <= 2'd1;
		result <= 8'b1;
	end
	
	else if (btnr) begin
		direction <= 2'd2;
		result <= 8'b1000_0000;
	end
	
	else begin
		direction <= direction;
		result <= result;
	end
	
	
	if (cnt==32'd0) case (direction)
		1: begin
			if (result==8'b1000_0000)
				result <= 8'b1;
			else
				result <= result << 1'b1;
		end
		2: begin
			if (result==8'b1)
				result <= 8'b1000_0000;
			else
				result <= result >> 1'b1;
		end
		default:
			result <= result;
	endcase
	
end


//8顆7-segment顯示 
assign {d7,d6,d5,d4,d3,d2,d1,d0} = scan;
assign dp = 1'b1; 
always@(posedge clk) begin
	counter <=(counter<=18'd100000) ? (counter + 18'd1) : 18'd0;
	state <= (counter==18'd100000) ? (state + 3'd1) : state;
	case(state)
		0:begin
			seg_number <= result[7];
			scan <= 8'b0111_1111;
		end
		1:begin
			seg_number <= result[6];
			scan <= 8'b1011_1111;
		end
		2:begin
			seg_number <= result[5];
			scan <= 8'b1101_1111;
		end
		3:begin
			seg_number <= result[4];
			scan <= 8'b1110_1111;
		end
		4:begin
			seg_number <= result[3];
			scan <= 8'b1111_0111; 
		end
		5:begin
			seg_number <= result[2];
			scan <= 8'b1111_1011; 
		end
		6:begin
			seg_number <= result[1];
			scan <= 8'b1111_1101; 
		end
		7:begin
			seg_number <= result[0];
			scan <= 8'b1111_1110; 
		end
		default:	state <= state;
	endcase
end  

//7-segment 輸出數字解碼
assign {g,f,e,d,c,b,a} = seg_data;
always@(posedge clk) begin  
  case(seg_number)
	16'd0:seg_data <= 7'b111_1111;
	16'd1:seg_data <= 7'b100_0000;
	16'd2:seg_data <= 7'b010_0100;
	16'd3:seg_data <= 7'b011_0000;
	16'd4:seg_data <= 7'b001_1001;
	16'd5:seg_data <= 7'b001_0010;
	16'd6:seg_data <= 7'b000_0010;
	16'd7:seg_data <= 7'b101_1000;
	16'd8:seg_data <= 7'b000_0000;
	16'd9:seg_data <= 7'b001_0000;
	default: seg_number <= seg_number;
  endcase
end 
endmodule
