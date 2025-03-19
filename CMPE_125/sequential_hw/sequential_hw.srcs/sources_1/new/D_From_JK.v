`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/18/2025 08:50:14 PM
// Design Name: 
// Module Name: D_From_JK
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


module D_From_JK(
    input D, clk,
    output Q
    );
    
    JK_Flip_Flop JKFF_inst(.J(D), .K(~D), .clk(clk), .Q(Q));
    
endmodule
