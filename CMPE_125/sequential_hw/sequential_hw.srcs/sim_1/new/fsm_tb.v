`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/18/2025 11:08:14 PM
// Design Name: 
// Module Name: fsm_tb
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

module fsm_tb();
    reg A, B, clk, reset;
    wire [1:0] Z;
    
    fsm UUT(
        .A(A),
        .B(B),
        .clk(clk),
        .reset(reset),
        .Z(Z)
    );
    
    always #5 clk = ~clk;
    
    initial begin
        clk = 0;
        reset = 1;
        A = 0;
        B = 0;
        
        #10 reset = 0;
        
        #10 A = 1; B = 0;
        #10 A = 0; B = 1;
        #10 A = 1; B = 1;
        
        #10 reset = 1;
        #10 reset = 0;
        
        // Test case 2
        #10 A = 0; B = 0;
        #10 A = 1; B = 1;
        
        #10 $finish;
    end
endmodule
