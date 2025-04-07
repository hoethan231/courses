`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/01/2024 06:13:54 PM
// Design Name: 
// Module Name: rle_latch
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


module rle_latch(
    input r, s, e,
    output Q, notQ
    );
    
    wire w1, w2;
    and #1 (w1, r, e);
    and #1 (w2, s, e);
    nor #1 (Q, w1, notQ);
    nor #1 (notQ, w2, Q);
    
endmodule
