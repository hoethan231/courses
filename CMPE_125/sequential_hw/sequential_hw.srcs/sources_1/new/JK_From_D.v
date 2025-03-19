`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/18/2025 08:27:26 PM
// Design Name: 
// Module Name: JK_From_D
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


module JK_From_D(
    input clk, J, K,
    output Q
);
    wire D;
    
    assign D = (~K & Q) | (J & ~Q);
    
    D_Flip_Flop dff_inst(.D(D), .clk(clk), .Q(Q));
    
endmodule
