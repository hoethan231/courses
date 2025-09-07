`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/06/2025 01:45:36 PM
// Design Name: 
// Module Name: datapath
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


module datapath(
    input clk, load_reg, load_cnt, SEL, OE, EN,
    input [31:0] n,
    output Error, GT,
    output [31:0] product
    );
      
    wire [31:0] count_out, reg_out, mul_out, mux1_out;
    
    comparator  CMP1(12, n, Error);
    counter     CNT(clk, EN, load_cnt, n, count_out);
    comparator  CMP2(n, 1, GT);
    multiplier  MUL(count_out, reg_out, mul_out);
    multiplexer MUX1(1, mul_out, SEL, mux1_out);
    register    REG(clk, load_reg, mux1_out, reg_out);
    multiplexer MUX2(0, reg_out, OE, product);
    
endmodule
