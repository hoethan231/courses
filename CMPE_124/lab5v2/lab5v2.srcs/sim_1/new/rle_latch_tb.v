`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/01/2024 06:21:18 PM
// Design Name: 
// Module Name: rle_latch_tb
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
module rle_latch_tb;
reg s, r, e;
wire Q, notQ;

rle_latch utt(
    .s(s), .r(r), .e(e), .Q(Q), .notQ(notQ)
    );

initial begin

    s <= 1'b0; r <= 1'b0; e <= 1'b0; #1;
    s <= 1'b1; r <= 1'b0; e <= 1'b0; #1;
    s <= 1'b0; r <= 1'b1; e <= 1'b0; #1;
    s <= 1'b1; r <= 1'b1; e <= 1'b0; #1;
    s <= 1'b0; r <= 1'b0; e <= 1'b1; #1;
    s <= 1'b1; r <= 1'b0; e <= 1'b1; #1;
    s <= 1'b0; r <= 1'b1; e <= 1'b1; #1;
    s <= 1'b1; r <= 1'b1; e <= 1'b1; #1;
    
    $finish;
    end
endmodule







