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

    CLA4 I(.a(a), .b(b), .ci(ci), .s(s), .co(co), .pg(pg), .gg(gg));
    initial begin
        
        a = 4'b0001; b = 4'b0001; ci = 1'b0; #5
        a = 4'b0011; b = 4'b0001; ci = 1'b0; #5
        a = 4'b0001; b = 4'b0001; ci = 1'b1; #5
        a = 4'b1001; b = 4'b0011; ci = 1'b1; #5
        a = 4'b1111; b = 4'b0000; ci = 1'b1; #5 //Overflow
        $finish;
    end

endmodule
