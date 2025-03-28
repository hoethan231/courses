`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/01/2024 03:53:49 PM
// Design Name: 
// Module Name: lr_latch_tb
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

module rl_latch_tb;
reg s, r;
wire Q, notQ;
rl_latch utt(
    .s(s), .r(r), .Q(Q), .notQ(notQ)
    );

initial 
    begin
        s <= 1'b0;
        r <= 1'b0;
        #4;
        s <= 1'b0;
        r <= 1'b1;
        #4;
        s <= 1'b1;
        r <= 1'b0;
        #4;
        s <= 1'b1;
        r <= 1'b1;
        #4;
    $finish;
    end
endmodule
