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
    input        clk,
    input        load_reg,
    input        load_cnt,
    input        SEL,
    input        OE,
    input        EN,
    input  [31:0] n,
    output       Error,
    output       GT,
    output [31:0] product
);

  wire [31:0] count_out, reg_out, mul_out, mux1_out;

  comparator CMP1 (
    .a(n),
    .b(32'd12),
    .Q(Error)
  );

  counter CNT (
    .clk      (clk),
    .en       (EN),
    .load_cnt (load_cnt),
    .n        (n),
    .Q        (count_out)
  );

  comparator CMP2 (
    .a(count_out),
    .b(32'd1),
    .Q(GT)
  );

  multiplier MUL (
    .a(count_out),
    .b(reg_out),
    .Q(mul_out)
  );

  multiplexer MUX1 (
    .a  (32'd1),
    .b  (mul_out),
    .sel(SEL),
    .Q  (mux1_out)
  );

  register REG (
    .clk     (clk),
    .load_reg(load_reg),
    .n       (mux1_out),
    .Q       (reg_out)
  );

  multiplexer MUX2 (
    .a  (32'd0),
    .b  (reg_out),
    .sel(OE),
    .Q  (product)
  );

endmodule