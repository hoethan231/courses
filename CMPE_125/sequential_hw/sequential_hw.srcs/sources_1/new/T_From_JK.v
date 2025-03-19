`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/18/2025 08:52:14 PM
// Design Name: 
// Module Name: T_From_JK
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


module T_From_JK(
    input T, clk,
    output Q
    );
    
    JK_Flip_Flop JKFF_Inst(.J(T), .K(T), .clk(clk), .Q(Q));
    
endmodule
