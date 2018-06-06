`timescale 1ns/1ps


module testbench();

	reg  [15:0] in_a, in_b;
	reg CLK;
	reg reset;
	reg  [15:0]correct_ans;
	wire  [15:0] out;
	reg [5:0]count;
	reg [5:0]ct;
	reg error;
	reg cin;	
	wire cout;

	reg  [15:0]temp_a;	
	reg  [15:0]temp_b;
	reg  [15:0] a,b;

	initial cin = 0;
	initial ct = 0;
	initial in_a = 0;
	initial in_b = 0;
/*	
	always@(posedge CLK or posedge reset)
	begin
		if(reset) begin
			{a,b} <= 30'b0;
		end else begin
			a   <= {$random} % 32768;	
			b   <= {$random} % 32768;
		end
	end
*/
	cla_16bit tp( in_a, in_b, cin, out, cout);
	
	/////// initial ///////
	initial begin

	//$fsdbDumpfile("dlab_11.fsdb");
	$dumpfile("lab9_16bit.fsdb");
	$dumpvars;
	CLK = 1'b0;
//	err_num = 0;
	#10 reset = 1;
	#20 reset = 0;
	
	#500 reset = 1;
	#20 reset = 0;
	#500 reset = 1;
	#20 reset = 0;
	#500 reset = 1;
	#20 reset = 0;
	#500 reset = 1;
	#20 reset = 0;
	#500 reset = 1;	
	#20 reset = 0;
	#500 reset = 1;
	#20 reset = 0;
	#500 reset = 1;
	#20 reset = 0;
	#500 reset = 1;
	#20 reset = 0;
	#500 reset = 1;
	#20 reset = 0;
	#500    $finish;
	
	end
	

	always #10 CLK = ~CLK;

	always @(posedge CLK or posedge reset)
	begin
		if(reset)
		begin
			count <= 0;
			in_a <= {$random} % 32767;
			in_b <= {$random} % 32767;
			correct_ans <= 0;
			error <= 0;
			ct <= ct + 1'b1;
		end
		else
		begin
			correct_ans <= in_a + in_b;
			count <= count +1;
			if(count == 2'b11)
				if(out != correct_ans)
				begin
	//				print = 0;
					error <=1;
					$display ();
					$display ("Test %d ", ct);
					$display ("//////////");
					$display ("// Fail //");
					$display ("//////////");
					$display ("%d + %d = ?", in_a, in_b);
					$display ("your answer is %d, but correct answer is %d\n", out, correct_ans);
					$display ();
				end
				else
				begin
	//				print = 0;
					error <= 0;
					$display ("Test %d ", ct);
					$display ("////////////////");
					$display ("// Successful //");
					$display ("////////////////");
					$display ("%d + %d = ?", in_a, in_b);
					$display ("your answer is %d,  correct answer is %d\n", out, correct_ans);
					$display ();
			end
		end


	end


endmodule
