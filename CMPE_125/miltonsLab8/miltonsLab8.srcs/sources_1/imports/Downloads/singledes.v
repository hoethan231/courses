`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/29/2025 06:31:38 PM
// Design Name: 
// Module Name: singledes
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

module single_port
#(
 ADDRESS_WIDTH = 5,
 DATA_WIDTH = 32
 )
 (
 input [ADDRESS_WIDTH - 1:0] a,b,c,
 input [DATA_WIDTH - 1: 0] w,
 input clk, we,
 output [DATA_WIDTH - 1:0] rd1 
 );
 
 reg [ADDRESS_WIDTH - 1: 0 ] memory [31: 0];
 reg [1:0] state, ns;
 reg [DATA_WIDTH - 1:0] out;
 
 parameter s0 = 2'b00;
 parameter s1 = 2'b01;
 parameter s2 = 2'b10;
 
 
 
 always @(posedge clk) begin
          state <= ns;
    case (state)
    s0:   begin
          out =  memory[a];
          ns = s1;
          end
    s1:   begin
          out = memory[b];
          ns = s2;
          end
    s2:   begin
          if(we)begin
          memory[c] = w;
          ns = s1;
          end
          else state = s2;
          end
         endcase
     end
  assign rd1 = out;
 endmodule
