`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/18/2025 09:23:41 PM
// Design Name: 
// Module Name: T_tb
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


module T_tb();
    reg T, clk;
    wire Q;
    
    T_From_JK TFromJK_Inst(.T(T), .clk(clk), .Q(Q));
    
    always #10 clk = ~clk;
    
    initial begin
        clk = 0;
        T = 0; #20;
        T = 1; #20;
        T = 0; #20;
        $finish();
    end
endmodule
