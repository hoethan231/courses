`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/19/2025 04:19:51 PM
// Design Name: 
// Module Name: prefixAdder
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


module prefixAdder(
    input [15:0] a, b,
    input cin,
    output [15:0] s,
    output cout
    );
    
    wire [14:0] p, g;
    wire [7:0] pij0, pij1, pij2, pij3, gij0, gij1, gij2, gij3;
    wire [15:0] gen;
    
    prop_gen pg(a[14:0], b[14:0], p, g);
    
    blackbox box0(
        {p[14], p[12], p[10], p[8], p[6], p[4], p[2], p[0]},
        {g[14], g[12], g[10], g[8], g[6], g[4], g[2], g[0]},
        {p[13], p[11], p[9], p[7], p[5], p[3], p[1], cin},
        {g[13], g[11], g[9], g[7], g[5], g[3], g[1], cin},
        pij0, gij0);
        
    blackbox box1(
        {pij0[7], p[13], pij0[5], p[9], pij0[3], p[5], pij0[1], p[1]},
        {gij0[7], g[13], gij0[5], g[9], gij0[3], g[5], gij0[1], g[1]},
        {{2{pij0[6]}}, {2{pij0[4]}}, {2{pij0[2]}}, {2{pij0[0]}}},
        {{2{gij0[6]}}, {2{gij0[4]}}, {2{gij0[2]}}, {2{gij0[0]}}},
        pij1, gij1);
        
    blackbox box2(
        {pij1[7], pij1[6], pij0[6], p[11], pij1[3], pij1[2], pij0[2], p[3]},
        {gij1[7], gij1[6], gij0[6], g[11], gij1[3], gij1[2], gij0[2], g[3]},
        {{4{pij1[5]}}, {4{pij1[1]}}},
        {{4{gij1[5]}}, {4{gij1[1]}}},
        pij2, gij2);
        
    blackbox box3(
        {pij2[7], pij2[6], pij2[5], pij2[4], pij1[5], pij1[4], pij0[4], p[7]},
        {gij2[7], gij2[6], gij2[5], gij2[4], gij1[5], gij1[4], gij0[4], g[7]},
        {8{pij2[3]}},
        {8{gij2[3]}},
        pij3, gij3);
    sumblock sum(a, b, gen, s);
    assign gen = {gij3, gij2[3:0], gij1[1:0],gij0[0], cin};
    assign cout = (a[15] & b[15] | gen[15] & (a[15] | b[15]));
endmodule
