`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/28/2025 06:24:05 AM
// Design Name: 
// Module Name: romdesign
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
 

 
 
 
module dualport#(parameter ADDRESS_WIDTH = 5, parameter DATA_WIDTH = 32) (

    input clka,clkb,we1,we2,
    input [ADDRESS_WIDTH - 1: 0] a, b,
    input [DATA_WIDTH -1 : 0] wd,wd2,
    output [DATA_WIDTH -1: 0] rd1, rd2
);
    reg [ADDRESS_WIDTH -1 : 0] memory [31:0];
    reg [DATA_WIDTH - 1:0] out1, out2;
    
always @(posedge clka, posedge clkb)begin
             if (clka) begin
             out1 = memory[a];
             if (we1) memory[a] = wd;
             end
             else if (clkb) begin
             out1 = memory[b];
             if(we2) memory[b] = wd2;
            end 
        end

    
endmodule




module trueport #(parameter ADDRESS_WIDTH = 5, parameter DATA_WIDTH = 32) (
    input clk,we1,we2,
    input [ADDRESS_WIDTH - 1: 0] a, b,
    input [DATA_WIDTH -1 : 0] wd, wd2,
    output [DATA_WIDTH -1: 0] rd1, rd2
);
    reg [ADDRESS_WIDTH -1 : 0] memory [31:0];
    reg [DATA_WIDTH - 1:0] out1, out2;
  always@ (posedge clk) begin
            out1 <= memory[a];
            out2 <= memory[b];    
    if(we1)  memory[a] <= wd;
    if(we2)  memory[b] <= wd2;
   end
   
   assign rd1 = out1;
   assign rd2 = out2;
endmodule
    
    

        







