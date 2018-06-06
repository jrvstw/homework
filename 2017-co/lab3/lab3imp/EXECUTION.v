`timescale 1ns/1ps

module EXECUTION(
    clk,
    rst,
    A,
    B,
    DX_RD,
    ALUctr,
    DX_CTRL,

    ALUout,
    XM_RD,
    XM_B,
    XM_CTRL
);

input clk,rst,ALUop;
input [31:0] A,B;
input [4:0]DX_RD;
input [2:0] ALUctr;
input [5:0] DX_CTRL;

output reg [31:0]ALUout;
output reg [4:0]XM_RD;
output reg [31:0] XM_B;
output reg [5:0] XM_CTRL;

//set pipeline register
always @(posedge clk or posedge rst) begin
    if(rst) begin
        XM_RD	<= 5'd0;
        XM_CTRL <= 5'd0;
        XM_B    <= 5'd0;
    end 
    else begin
        XM_RD <= DX_RD;
        XM_CTRL <= DX_CTRL;
        XM_B    <= XM_B;
    end
end

// calculating ALUout
always @(posedge clk or posedge rst) begin
    if(rst) begin
        ALUout	<= 32'd0;
    end 
    else begin
        case(ALUctr)
            3'b000: // and
            begin
                ALUout <= A&B;
            end
            3'b001: // or
            begin
                ALUout <= A|B;
            end
            3'b010: //add //lw //sw
            begin
                ALUout <=A+B;
            end
            3'b110: //sub
            begin
                //define sub behavior here
                ALUout <=A-B;
            end
            3'b111: //slt
            begin
                ALUout <= (A<B)? 1: 0;
            end
        endcase
    end
end
endmodule

