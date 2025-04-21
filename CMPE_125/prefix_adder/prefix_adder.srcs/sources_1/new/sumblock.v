`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/19/2025 04:15:11 PM
// Design Name: 
// Module Name: sumblock
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


module sumblock(
    input [15:0] a, b, g,
    output [15:0] s
    );
    
    assign s = g ^ a ^ b;
    
endmodule
