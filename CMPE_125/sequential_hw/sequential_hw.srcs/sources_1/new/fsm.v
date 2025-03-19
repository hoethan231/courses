`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/18/2025 10:55:35 PM
// Design Name: 
// Module Name: fsm
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


module fsm(
    input A, B, clk, reset,
    output reg [1:0] Z
    );
    
    reg [1:0] curr, next;
    initial curr <= 2'b00;
    always@(posedge clk, posedge reset) begin
        if (reset)
            Z <= 2'b00;
        else 
            Z <= next;
        end
        
     always @(*) begin
        casez({curr, A, B})
            4'b00_0_z: next = 2'b00;
            4'b00_1_0: next = 2'b11;
            4'b00_1_1: next = 2'b01;
            4'b01_0_0: next = 2'b00;
            4'b01_1_0: next = 2'b11;
            4'b01_0_1: next = 2'b10;
            4'b01_1_1: next = 2'b01;
            4'b10_z_0: next = 2'b00;
            4'b10_0_1: next = 2'b10;
            4'b10_1_1: next = 2'b01;
            4'b10_0_0: next = 2'b00;
            4'b11_0_0: next = 2'b00;
            4'b11_1_0: next = 2'b11;
            4'b11_0_1: next = 2'b10;
            4'b11_1_1: next = 2'b01;
            default: next = 2'b00;
         endcase
         Z = (A&B) | (curr[0] & (A | B));
     end
endmodule
