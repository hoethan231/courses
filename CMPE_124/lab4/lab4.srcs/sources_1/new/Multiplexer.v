`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/09/2024 09:21:32 AM
// Design Name: 
// Module Name: Multiplexer
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


module Multiplexer(
    input A,
    input B,
    input select,
    output out
    );
    wire out1, out2;
    not(selectn, select);
    and(out1, A, selectn);
    and(out2, B, select);
    or(out, out1, out2);
    
endmodule
