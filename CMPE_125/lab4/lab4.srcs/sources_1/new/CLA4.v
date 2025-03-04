`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/03/2025 08:19:55 PM
// Design Name: 
// Module Name: CLA4
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


module CLA4(
    input [3:0] a, [3:0] b, ci,
    output [3:0] s, co, pg, gg
    );
    
    wire [3:0] g;
    wire [3:0] p;
    wire [3:1] c;
    
    CLALogic logic(g, p, ci, c, co, pg, gg);
    GPFullAdder one(a[0], b[0], ci, g[0], p[0], s[0]);
    GPFullAdder two(a[1], b[1], c[1], g[1], p[1], s[1]);
    GPFullAdder three(a[2], b[2], c[2], g[2], p[2], s[2]);
    GPFullAdder four(a[3], b[3], c[3], g[3], p[3], s[3]);
    
endmodule
