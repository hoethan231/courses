`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/18/2025 08:59:55 PM
// Design Name: 
// Module Name: JK_tb
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


module JK_tb();
    reg J, K, clk;
    wire Q_JKFF;
    wire Q_JKFromD;
    
    JK_Flip_Flop JKFF_inst(.J(J), .K(K), .clk(clk), .Q(Q_JKFF));
    JK_From_D JKFromD_inst(.J(J), .K(K), .clk(clk), .Q(Q_JKFromD));
    
    always #5 clk = ~clk;
    
    initial begin
        clk = 0;
        J = 0; K = 0; #10
        J = 0; K = 1; #10
        J = 1; K = 0; #10
        J = 1; K = 1; #10
        $finish();
    end
endmodule
