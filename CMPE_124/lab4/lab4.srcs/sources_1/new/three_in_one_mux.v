`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/09/2024 10:21:55 AM
// Design Name: 
// Module Name: three_in_one_mux
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


module three_in_one_mux(
    input A,
    input B,
    input C,
    input select0,
    input select1,
    output out
    );
    wire out1, out2, out3, out4, out5;
    not(select0n, select0);
    and(out1, A, select0n);
    and(out2, B, select0);
    or(out3, out1, out2);
    
    not(select1n, select1);
    and(out4, out3, select1n);
    and(out5, C, select0);
    or(out, out4, out5);
    
endmodule