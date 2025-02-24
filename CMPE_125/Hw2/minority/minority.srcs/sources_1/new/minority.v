`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/23/2025 06:23:57 PM
// Design Name: 
// Module Name: minority
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


module minority(
    input a, b, c,
    output y
    );
    
    assign y = (a ^ b ^ c) & ~(a & b & c);
    
endmodule
