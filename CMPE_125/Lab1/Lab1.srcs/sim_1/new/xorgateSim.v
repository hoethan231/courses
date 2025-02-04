`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/04/2025 10:38:43 AM
// Design Name: 
// Module Name: xorgateSim
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


module xorgateSim;
wire f;
reg x1, x2;

xorgate utt(.x1(x1), .x2(x2), .f(f));
    
initial begin
    x1 = 0; x2 = 0; #1
    x1 = 0; x2 = 1; #1
    x1 = 1; x2 = 0; #1
    x1 = 1; x2 = 1; #1
    $finish;

end
endmodule
