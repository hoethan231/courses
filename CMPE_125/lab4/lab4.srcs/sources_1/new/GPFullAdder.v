`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/03/2025 08:18:10 PM
// Design Name: 
// Module Name: GPFullAdder
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


module GPFullAdder(
    input Ai, Bi, Cin,
    output G, P, Sum
    );

    assign P = Ai ^ Bi;
    assign G = Ai & Bi;
    assign Sum = P ^ Cin;

endmodule
