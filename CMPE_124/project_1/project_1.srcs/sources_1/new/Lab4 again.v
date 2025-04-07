`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/02/2024 10:19:12 AM
// Design Name: 
// Module Name: Lab4 again
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


module Lab4_again(
    input A,
    input B,
    input select,
    output y
    );
    wire out1, out2;
    not(selectn, select);
    and(out1, A, selectn);
    and(out2, B, select);
    or(out, out1, out2);
    
endmodule
