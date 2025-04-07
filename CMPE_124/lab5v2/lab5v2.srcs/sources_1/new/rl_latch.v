`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/01/2024 03:51:44 PM
// Design Name: 
// Module Name: rl_latch
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


module rl_latch(
    input s, r,
    output Q, notQ
    );
    
    nor #5 (Q, r, notQ);
    nor #5 (notQ, Q, s);
endmodule
