`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/21/2025 08:50:17 PM
// Design Name: 
// Module Name: 32BitALU
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module ALU(
    input [2:0] F,
    input [31:0] a, b,
    output reg [31:0] c,
    output reg ZR, OV, CF
    );
    
    always @(*) begin
        OV = 1'b0;
        ZR = 1'b0;
        CF = 1'b0;
        case (F)
            3'b000: c = a & b;
            3'b001: c = a | b;
            3'b010: begin
                {CF, c} = a + b; 
                OV = (a[31] == b[31] && a[31] != c[31])? 1'b1 : 1'b0;
                end
            3'b100: c = a & ~b;
            3'b101: c = a | ~b;
            3'b110: begin
                {CF, c} = a - b;
                OV = (a[31] != b[31] && a[31] != c[31])? 1'b1 : 1'b0;
                end
            3'b111: c = (a < b) ? 32'b1 : 32'b0;
            default: begin
                {CF, c} = a + b; 
                OV = (a[31] == b[31] && a[31] != c[31])? 1'b1 : 1'b0;
                end
        endcase
        ZR = (c == 32'b0) ? 1'b1 : 1'b0;
    end
endmodule
