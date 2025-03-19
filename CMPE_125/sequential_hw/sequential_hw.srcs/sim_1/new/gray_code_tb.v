`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/18/2025 10:23:06 PM
// Design Name: 
// Module Name: gray_code_tb
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


module gray_code_tb();
reg clk, reset;
wire [2:0] code;

    gray_code uut(.reset(reset), .clk(clk), .code(code));
    
    always #5 clk = ~clk;
    
    initial begin
        reset = 1;
        clk = 0; #5
        reset = 0; #90
        $finish();
    end

endmodule
