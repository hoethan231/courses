`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/18/2025 09:19:34 PM
// Design Name: 
// Module Name: D_tb
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


module D_tb();
reg D, clk;
wire DFF, DFromJK;

    D_Flip_Flop DFF_Inst(.D(D), .clk(clk), .Q(DFF));
    D_From_JK DFromJK_Inst(.D(D), .clk(clk), .Q(DFromJK));
    
    always #10 clk = ~clk;
    initial begin
        clk = 0;
        D = 1'b0; #20;
        D = 1'b1; #20;
        D = 1'b0; #20;
        $finish();
    end

endmodule
