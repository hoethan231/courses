`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/23/2025 05:57:57 PM
// Design Name: 
// Module Name: xorGate
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


module xorGate(
    input [3:0] a,
    output y
    );
    
    assign y = a[0] ^ a[1] ^ a[2] ^ a[3];
    
endmodule
