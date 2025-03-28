`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/30/2024 09:44:11 AM
// Design Name: 
// Module Name: sr_latch_tb
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
module sr_latch_tb;

reg S, R;
wire Q, notQ;
//reg [1:0] test_cases [4:0];

sr_latch utt(
    .S(R), 
    .R(R), 
    .Q(Q), 
    .notQ(notQ)
);
initial begin 

//    test_cases[0] = 2'b00;
//    test_cases[1] = 2'b01;
//    test_cases[2] = 2'b10;
//    test_cases[4] = 2'b11;

//    for(integer i=0; i<4; i=i+1) begin
//        {S, R} = test_cases[i];
//        #1;
        S <= 1'b0; R <= 1'b0; 
        #5; 
        S <= 1'b0; R <= 1'b1;
        #5; 
        S <= 1'b1; R <= 1'b0;
        #5; 
        S <= 1'b1; R <= 1'b1;
        #5;
//    end
        $finish;
    end
endmodule





