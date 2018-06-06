//------------------------------------------------------//
//- DD 2013                                             //
//                                                      //
//- Lab 9: CLA (Verilog  RTL)                           //
//-	TA : Bo-Yu Su										//
//  e-mail : starrain_18@hotmail.com                    //
//------------------------------------------------------//
 
`timescale 1ns/1ps
module cla_64bit( a, b, cin, out, cout);

	input [63:0] a, b;
	output [63:0] out;
	input cin;
	output cout;

    wire [63:0] p, g;
    wire [15:0] p_4, g_4;
    wire [3:0] p_16, g_16;
    wire [16:0] c;
    wire [4:0] c_16;
    assign cout = c_16[4];
	
	//write your design below
	pg_generator pg1(a[3:0], b[3:0], p[3:0], g[3:0]);
	pg_generator pg2(a[7:4], b[7:4], p[7:4], g[7:4]);
	pg_generator pg3(a[11:8], b[11:8], p[11:8], g[11:8]);
	pg_generator pg4(a[15:12], b[15:12], p[15:12], g[15:12]);
	pg_generator pg5(a[19:16], b[19:16], p[19:16], g[19:16]);
	pg_generator pg6(a[23:20], b[23:20], p[23:20], g[23:20]);
	pg_generator pg7(a[27:24], b[27:24], p[27:24], g[27:24]);
	pg_generator pg8(a[31:28], b[31:28], p[31:28], g[31:28]);
	pg_generator pg9(a[35:32], b[35:32], p[35:32], g[35:32]);
	pg_generator pg10(a[39:36], b[39:36], p[39:36], g[39:36]);
	pg_generator pg11(a[43:40], b[43:40], p[43:40], g[43:40]);
	pg_generator pg12(a[47:44], b[47:44], p[47:44], g[47:44]);
	pg_generator pg13(a[51:48], b[51:48], p[51:48], g[51:48]);
	pg_generator pg14(a[55:52], b[55:52], p[55:52], g[55:52]);
	pg_generator pg15(a[59:56], b[59:56], p[59:56], g[59:56]);
	pg_generator pg16(a[63:60], b[63:60], p[63:60], g[63:60]);

	group_CLA_4bit sum1(p[3:0], g[3:0], c[0], g_4[0], p_4[0], , out[3:0]);
	group_CLA_4bit sum2(p[7:4], g[7:4], c[1], g_4[1], p_4[1], , out[7:4]);
	group_CLA_4bit sum3(p[11:8], g[11:8], c[2], g_4[2], p_4[2], , out[11:8]);
	group_CLA_4bit sum4(p[15:12], g[15:12], c[3], g_4[3], p_4[3], , out[15:12]);
	group_CLA_4bit sum5(p[19:16], g[19:16], c[4], g_4[4], p_4[4], , out[19:16]);
	group_CLA_4bit sum6(p[23:20], g[23:20], c[5], g_4[5], p_4[5], , out[23:20]);
	group_CLA_4bit sum7(p[27:24], g[27:24], c[6], g_4[6], p_4[6], , out[27:24]);
	group_CLA_4bit sum8(p[31:28], g[31:28], c[7], g_4[7], p_4[7], , out[31:28]);
	group_CLA_4bit sum9(p[35:32], g[35:32], c[8], g_4[8], p_4[8], , out[35:32]);
	group_CLA_4bit sum10(p[39:36], g[39:36], c[9], g_4[9], p_4[9], , out[39:36]);
	group_CLA_4bit sum11(p[43:40], g[43:40], c[10], g_4[10], p_4[10], , out[43:40]);
	group_CLA_4bit sum12(p[47:44], g[47:44], c[11], g_4[11], p_4[11], , out[47:44]);
	group_CLA_4bit sum13(p[51:48], g[51:48], c[12], g_4[12], p_4[12], , out[51:48]);
	group_CLA_4bit sum14(p[55:52], g[55:52], c[13], g_4[13], p_4[13], , out[55:52]);
	group_CLA_4bit sum15(p[59:56], g[59:56], c[14], g_4[14], p_4[14], , out[59:56]);
	group_CLA_4bit sum16(p[63:60], g[63:60], c[15], g_4[15], p_4[15], , out[63:60]);

  	group_CLA_4bit carry_generator1(p_4[3:0], g_4[3:0], c_16[0], g_16[0], p_16[0], c[4:0], );
  	group_CLA_4bit carry_generator2(p_4[7:4], g_4[7:4], c_16[1], g_16[1], p_16[1], c[8:4], );
  	group_CLA_4bit carry_generator3(p_4[11:8], g_4[11:8], c_16[2], g_16[2], p_16[2], c[12:8], );
  	group_CLA_4bit carry_generator4(p_4[15:12], g_4[15:12], c_16[3], g_16[3], p_16[3], c[16:12], );

  	group_CLA_4bit carry_generator(p_16[3:0], g_16[3:0], cin, , , c_16[4:0], );

	
endmodule


module group_CLA_4bit( p, g, cin, gG, gP, c, sum);

	input [3:0] p, g;
	input cin;
	output gG, gP;
	output [4:0] c;
	output	[3:0] sum;

	assign gG = (g[0] & p[1] & p[2] & p[3])|(g[1]&p[2]&p[3])|(g[2]&p[3])|g[3];
	assign gP = p[0] & p[1] & p[2] & p[3];
		
	assign c[0] = cin;
	assign c[1] = g[0]|(p[0] & cin);
	assign c[2] = g[1]|(p[1] & g[0])|(p[1] & p[0] & cin);
	assign c[3] = g[2]|(p[2] & g[1])|(p[2] & p[1] & g[0])|(p[2] & p[1] & p[0] & cin);
	assign c[4] = g[3]|(p[3] & g[2])|(p[3] & p[2] & g[1])|(p[3] & p[2] & p[1] & g[0])|(p[3] & p[2] & p[1] & p[0] & cin);
		
	assign sum[0] = c[0] ^ p[0];
	assign sum[1] = c[1] ^ p[1];
	assign sum[2] = c[2] ^ p[2];
	assign sum[3] = c[3] ^ p[3];
		
endmodule


module pg_generator( a, b, p, g);

        input [3:0] a, b;
        output [3:0] p, g;

        // Carry Propagate
        assign p[0] = a[0] ^ b[0] ;
        assign p[1] = a[1] ^ b[1] ;
        assign p[2] = a[2] ^ b[2] ;
        assign p[3] = a[3] ^ b[3] ;
        //carry Generate
        assign g[0] = a[0] & b[0] ;
        assign g[1] = a[1] & b[1] ;
    	assign g[2] = a[2] & b[2] ;
        assign g[3] = a[3] & b[3] ;

endmodule

