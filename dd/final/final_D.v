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
    input sw0,
    input sw1,
    input sw2,
    input sw3,
    input sw4,
    input sw5,
    input sw6,
    input sw7,
    input sw8,
    input sw9,
    input sw10,
    input sw11,
    input sw12,
    input sw13,
    input sw14,
    input sw15,
	 input btnc,
	 input btnd,
	 input btnl,
	 input btnr,
	 input btnu,
	 
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
	 output led15,
	 output led16_b,
	 output led16_g,
	 output led16_r,
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

reg [31:0] cycle = 0;
reg [31:0] delay = 32'd50000000;
reg [15:0] random = 0;

reg [1:0] alert = 0;
reg [1:0] state = 0;
reg [15:0] place = 16'b1;
reg [15:0] mine = 0;

reg [2:0] number;

reg [17:0] counter;
reg [2:0] state2;
reg [6:0] seg_number,seg_data;
reg [7:0] scan;


  clock instance_name
   (// Clock in ports
    .CLK_IN1(clk),      // IN
    // Clock out ports
    .CLK_OUT1(CLK_OUT1),     // OUT
    .CLK_OUT2(CLK_OUT2),     // OUT
    .CLK_OUT3(CLK_OUT3),     // OUT
    // Status and control signals
    .RESET(btnc));       // IN

always@(posedge CLK_OUT3)begin
	cycle  <=  (cycle>=1000000)?   32'b0:    cycle + 32'b1;
	delay  <=    (delay<=32'b0)?   32'b0:  (delay - 32'b1);
	random <= random + 16'b1;
	
	if (btnu) begin
		delay <= 32'd50000000;
		alert <= 2'b0;
		state <= 2'b0;
		place <= 16'b1;
		mine  <= {sw15,sw14,sw13,sw12,sw11,sw10,sw9,sw8,sw7,sw6,sw5,sw4,sw3,sw2,sw1,sw0};
	end
	if (btnc) begin
		delay <= 32'd50000000;
		alert <= 2'b0;
		state <= 2'b0;
		place <= 16'b1;
		mine  <= random;
	end
	if (btnl && state==2'b0 && delay==32'b0) begin
		delay <= 32'd20000000;
		if (place==16'b1000_0000_0000_0000)
			place <= 16'b1;
		else
			place <= place << 1'b1;
	end
	if (btnr && state==2'b0 && delay==32'b0) begin
		delay <= 32'd20000000;
		if (place==16'b1)
			place <= 16'b1000_0000_0000_0000;
		else
			place <= place >> 1'b1;
	end
	if (btnd) begin
		delay <= 32'd50000000;
		alert <= ({sw15,sw14,sw13,sw12,sw11,sw10,sw9,sw8,sw7,sw6,sw5,sw4,sw3,sw2,sw1,sw0}==mine)? 2'd2: 2'd1;
		state <= 2'b1;
	end

		if (cycle==32'd0) case (place) 
		16'b0000_0000_0000_0001:  number <= {2'b0,mine[0]} + {2'b0,mine[1]};
		16'b0000_0000_0000_0010:  number <= {2'b0,mine[0]} + {2'b0,mine[1]} + {2'b0,mine[2]};
		16'b0000_0000_0000_0100:  number <= {2'b0,mine[1]} + {2'b0,mine[2]} + {2'b0,mine[3]};
		16'b0000_0000_0000_1000:  number <= {2'b0,mine[2]} + {2'b0,mine[3]} + {2'b0,mine[4]};
		16'b0000_0000_0001_0000:  number <= {2'b0,mine[3]} + {2'b0,mine[4]} + {2'b0,mine[5]};
		16'b0000_0000_0010_0000:  number <= {2'b0,mine[4]} + {2'b0,mine[5]} + {2'b0,mine[6]};
		16'b0000_0000_0100_0000:  number <= {2'b0,mine[5]} + {2'b0,mine[6]} + {2'b0,mine[7]};
		16'b0000_0000_1000_0000:  number <= {2'b0,mine[6]} + {2'b0,mine[7]} + {2'b0,mine[8]};
		16'b0000_0001_0000_0000:  number <= {2'b0,mine[7]} + {2'b0,mine[8]} + {2'b0,mine[9]};
		16'b0000_0010_0000_0000:  number <= {2'b0,mine[8]} + {2'b0,mine[9]} + {2'b0,mine[10]};
		16'b0000_0100_0000_0000: number <= {2'b0,mine[9]} + {2'b0,mine[10]} + {2'b0,mine[11]};
		16'b0000_1000_0000_0000: number <= {27'b0,mine[10]} + {2'b0,mine[11]} + {2'b0,mine[12]};
		16'b0001_0000_0000_0000: number <= {2'b0,mine[11]} + {2'b0,mine[12]} + {2'b0,mine[13]};
		16'b0010_0000_0000_0000: number <= {2'b0,mine[12]} + {2'b0,mine[13]} + {2'b0,mine[14]};
		16'b0100_0000_0000_0000: number <= {2'b0,mine[13]} + {2'b0,mine[14]} + {2'b0,mine[15]};
		16'b1000_0000_0000_0000: number <= {2'b0,mine[14]} + {2'b0,mine[15]};		default: number <= number;
		endcase
	
	
end

//8顆7-segment顯示 
assign {d7,d6,d5,d4,d3,d2,d1,d0} = scan;
assign dp = 1'b1; 
always@(posedge CLK_OUT3) begin
	counter <=(counter<=18'd100000) ? (counter + 18'd1) : 18'd0;
	state2 <= (counter==18'd100000) ? (state2 + 3'd1) : state2;
	case(state2)
		0:begin
			seg_number <= 16'd8;
			scan <= 8'b0111_1111;
		end
		1:begin
			seg_number <= 16'd8;
			scan <= 8'b1011_1111;
		end
		2:begin
			seg_number <= 16'd8;
			scan <= 8'b1101_1111;
		end
		3:begin
			seg_number <= 16'd8;
			scan <= 8'b1110_1111;
		end
		4:begin
			seg_number <= 16'd8;
			scan <= 8'b1111_0111; 
		end
		5:begin
			seg_number <= 16'd8;
			scan <= 8'b1111_1011; 
		end
		6:begin
			seg_number <= 16'd8;
			scan <= 8'b1111_1101; 
		end
		7:begin
			seg_number <= number;
			scan <= 8'b1111_1110; 
		end
		default:	state2 <= state2;
	endcase
end

//7-segment 輸出數字解碼
assign {g,f,e,d,c,b,a} = seg_data;
always@(posedge CLK_OUT3) begin  
  case(seg_number)
	7'd0:seg_data <= 7'b100_0000;
	7'd1:seg_data <= 7'b111_1001;
	7'd2:seg_data <= 7'b010_0100;
	7'd3:seg_data <= 7'b011_0000;
	7'd4:seg_data <= 7'b001_1001;
	7'd5:seg_data <= 7'b001_0010;
	7'd6:seg_data <= 7'b000_0010;
	7'd7:seg_data <= 7'b101_1000;
	7'd8:seg_data <= 7'b111_1111;
	7'd9:seg_data <= 7'b001_0000;
	default: seg_number <= seg_number;
  endcase
end 


assign {led15,led14,led13,led12,led11,led10,led9,led8,led7,led6,led5,led4,led3,led2,led1,led0} = (state==2'b1)? mine: place;

assign led16_r = (alert==2'd1)? CLK_OUT2: CLK_OUT3;
assign led16_g = (alert==2'd2)? CLK_OUT2: CLK_OUT3;
assign led16_b = CLK_OUT3;

endmodule
