`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/23/2025 06:03:33 PM
// Design Name: 
// Module Name: xorGateTB
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


module xorGateTB();
reg [3:0] a;
wire y;

    xorGate I(.a(a), .y(y));
    initial begin
        a = 4'b0000; #5
        a = 4'b0001; #5
        a = 4'b0010; #5
        a = 4'b0011; #5
        a = 4'b0100; #5
        a = 4'b0101; #5
        a = 4'b0110; #5
        a = 4'b0111; #5
        a = 4'b1000; #5
        a = 4'b1001; #5
        a = 4'b1010; #5
        a = 4'b1011; #5
        a = 4'b1100; #5
        a = 4'b1101; #5
        a = 4'b1110; #5
        a = 4'b1111; #5
        $finish;
       end        
endmodule
