`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/03/2025 08:36:08 PM
// Design Name: 
// Module Name: CLA4TB
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


module CLA4TB();

reg [3:0] a;
reg [3:0] b;
reg ci;

wire [3:0] s;
wire co;
wire pg;
wire gg;

    CLA4 uut(.a(a), .b(b), .ci(ci), .s(s), .co(co), .pg(pg), .gg(gg));
    integer i, j, k;
    initial begin
        for(i=0; i<16; i=i+1) begin
            for(j=0;j<16;j=j+1) begin
                for(k=0;k<2;k=k+1) begin
                    a = i; b = j; ci = k; #10;
                end
            end
        end
        $finish();
    end
endmodule
