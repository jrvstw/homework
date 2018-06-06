`define    ADD 2'b00
`define    SUB 2'b01
`define    AND 2'b10
`define    OR  2'b11

module ALU( Data_A, Data_B, OP_Code, ALU_CLK, ALU_RST, Data_Out );

	input    ALU_CLK, ALU_RST;
    input   [3:0] Data_A, Data_B;
    input   [1:0] OP_Code;
    output reg [7:0] Data_Out;
	
    always @(posedge ALU_CLK) begin
		if(ALU_RST)
			Data_Out <= 0;
		else if ( OP_Code == 2'b00)
			Data_Out <= Data_A + Data_B;
		else if ( OP_Code == 2'b01)
			Data_Out <= Data_A - Data_B;
		else if( OP_Code == 2'b10)
			Data_Out <= Data_A & Data_B;
		else if ( OP_Code == 2'b11)
			Data_Out <= Data_A | Data_B;
		else
			Data_Out <= Data_Out;
        /*case( OP_Code )
            2'b00:       Data_Out <= Data_A + Data_B;
            2'b01:       Data_Out <= Data_A - Data_B;
            2'b10:       Data_Out <= Data_A & Data_B;
            2'b11:       Data_Out <= Data_A | Data_B;
            default:    Data_Out <= Data_Out;
        endcase*/
    end

endmodule