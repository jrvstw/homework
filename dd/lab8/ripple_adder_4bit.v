module full_adder(sum, cout, a, b, cin);
//port declaration
	output	sum, cout; 
	input	a, b, cin;  
// data type declaration 
	//wire	[1:0] result; 
// behavior description 
wire x,y,z;
xor i1(x,a,b);
xor i2(sum,x,cin);
and i3(y,x,cin);
and i4(z,a,b);
or i5(cout,y,z);

endmodule

module _4bit_adder_structural(sum, cout, a, b, cin);
//port declaration
	output	[3:0]sum;
	output  cout;
	input	[3:0]a, b;
	input 	cin; 
    wire [2:0]c;
//write your design 	
	full_adder fa0(.sum(sum[0]),.cout(c[0]),.a(a[0]),.b(b[0]),.cin(cin));
	full_adder fa1(.sum(sum[1]),.cout(c[1]),.a(a[1]),.b(b[1]),.cin(c[0]));
	full_adder fa2(.sum(sum[2]),.cout(c[2]),.a(a[2]),.b(b[2]),.cin(c[1]));
	full_adder fa3(.sum(sum[3]),.cout(cout),.a(a[3]),.b(b[3]),.cin(c[2]));


endmodule

/*
module _16bit_adder_structural(sum, cout, a, b, cin);
	output	[15:0]sum;
	output  cout;
	input	[15:0]a, b;
	input 	cin; 
// write your design 	
	
	_4bit_adder_structural fa0(.sum(sum[3:0]),.cout(c0),.a(a[3:0]),.b(b[3:0]),.cin(cin));
	_4bit_adder_structural fa1(.sum(sum[7:4]),.cout(c1),.a(a[7:4]),.b(b[7:4]),.cin(c0));
	_4bit_adder_structural fa2(.sum(sum[11:8]),.cout(c2),.a(a[11:8]),.b(b[11:8]),.cin(c1));
	_4bit_adder_structural fa3(.sum(sum[15:12]),.cout(cout),.a(a[15:12]),.b(b[15:12]),.cin(c2));
	

endmodule
*/






