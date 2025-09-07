`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/06/2025 04:12:41 PM
// Design Name: 
// Module Name: factorial_program
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


module factorial_program(
    input clk, go,
    input [31:0] n,
    output done, error,
    output [31:0] Q
    );
    
    wire load_reg, load_cnt, SEL, OE, EN, Error, GT;
    
    datapath        DP(clk, load_reg, load_cnt, SEL, OE, EN, n, Error, GT, Q);
    control_unit    CU(clk, go, Error, GT, SEL, load_reg, load_cnt, OE, EN, done, error);
    
endmodule
