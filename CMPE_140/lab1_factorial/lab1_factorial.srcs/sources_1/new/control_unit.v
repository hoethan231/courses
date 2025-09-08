`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/06/2025 02:20:25 PM
// Design Name: 
// Module Name: control_unit
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


module control_unit(
    input  clk,
    input  rst,
    input  GO,
    input  Error,
    input  GT,
    output reg SEL,
    output reg load_reg,
    output reg load_cnt,
    output reg OE,
    output reg EN,
    output reg done,
    output reg error
);

  reg [2:0] curr, next;

  localparam S0 = 3'b000;
  localparam S1 = 3'b001;
  localparam S2 = 3'b010;
  localparam S3 = 3'b011;
  localparam S4 = 3'b100;

  always @(posedge clk or posedge rst) begin
    if (rst) curr <= S0;
    else     curr <= next;
  end

  always @* begin
    next      = curr;
    SEL       = 1'b0;
    load_reg  = 1'b0;
    load_cnt  = 1'b0;
    OE        = 1'b0;
    EN        = 1'b0;
    done      = 1'b0;
    error     = 1'b0;

    case (curr)
      S0: begin
        if (GO) next = S1;
      end

      S1: begin
        if (!Error) begin
          load_reg = 1'b1;
          load_cnt = 1'b1;
          next     = S2;
        end else begin
          error    = 1'b1;
          next     = S0;
        end
      end

      S2: begin
        if (GT) begin
          SEL  = 1'b1;
          next = S3;
        end else begin
          OE   = 1'b1;
          done = 1'b1;
          next = S4;
        end
      end

      S3: begin
        SEL      = 1'b1;
        load_reg = 1'b1;
        EN       = 1'b1;
        next     = S2;
      end

      S4: begin
        OE   = 1'b1;
        done = 1'b1;
        next = S0;
      end
    endcase
  end

endmodule
