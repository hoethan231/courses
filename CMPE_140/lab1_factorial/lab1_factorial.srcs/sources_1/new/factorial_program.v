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
    input        clk,
    input        rst,
    input        go,
    input  [31:0] n,
    output       done,
    output       error,
    output [31:0] Q
);

  wire load_reg, load_cnt, SEL, OE, EN, Error, GT;

  datapath DP (
    .clk      (clk),
    .load_reg (load_reg),
    .load_cnt (load_cnt),
    .SEL      (SEL),
    .OE       (OE),
    .EN       (EN),
    .n        (n),
    .Error    (Error),
    .GT       (GT),
    .product  (Q)
  );

  control_unit CU (
    .clk      (clk),
    .rst      (rst),
    .GO       (go),
    .Error    (Error),
    .GT       (GT),
    .SEL      (SEL),
    .load_reg (load_reg),
    .load_cnt (load_cnt),
    .OE       (OE),
    .EN       (EN),
    .done     (done),
    .error    (error)
  );

endmodule
