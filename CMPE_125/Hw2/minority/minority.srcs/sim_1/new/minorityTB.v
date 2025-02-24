`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/23/2025 06:24:20 PM
// Design Name: 
// Module Name: minorityTB
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


module minorityTB();
reg a, b, c;
wire y;

    minority I(.a(a), .b(b), .c(c), .y(y));
    initial begin
        a = 0; b = 0; c = 0; #5
        a = 0; b = 0; c = 1; #5
        a = 0; b = 1; c = 0; #5
        a = 0; b = 1; c = 1; #5
        a = 1; b = 0; c = 0; #5
        a = 1; b = 0; c = 1; #5
        a = 1; b = 1; c = 0; #5
        a = 1; b = 1; c = 1; #5
        $finish();
    end
endmodule
