`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/19/2025 04:09:31 PM
// Design Name: 
// Module Name: prop_gen
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


module prop_gen(
    input [14:0] a, b,
    output [14:0] p, g
    );
    assign g = a & b;
    assign p = a | b;
    
endmodule
