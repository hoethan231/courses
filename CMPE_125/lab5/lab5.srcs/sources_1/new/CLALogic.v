`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/04/2025 08:19:55 PM
// Design Name: 
// Module Name: CLALogic
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


module CLALogic(
    input [3:0] g,
    input [3:0] p,
    input ci,
    output [3:1] c,
    output co,
    output pg,
    output gg
    );
    
    assign c[1] = g[0] | (p[0] & ci);
    assign c[2] = g[1] | (p[1] & g[0]) | (p[1] & p[0] & ci);
    assign c[3] = g[2] | (p[2] & g[1]) | (p[2] & p[1] & g[0]) | (p[2] & p[1] & p[0] & ci);
    
    assign pg = p[3] & p[2] & p[1] & p[0];
    assign gg = g[3] | (p[3] & g[2]) | (p[3] & p[2] & g[1]) | (p[3] & p[2] & p[1] & g[0]);
    assign co = gg | (pg & ci);
    
endmodule