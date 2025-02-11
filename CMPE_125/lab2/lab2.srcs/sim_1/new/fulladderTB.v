`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/11/2025 01:55:13 AM
// Design Name: 
// Module Name: fulladderTB
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


module fulladderTB();
reg A, B, Cin;
wire S, Cout;

    fulladder  I(.A(A), .B(B), .Cin(Cin), .S(S), .Cout(Cout));
    initial begin
        A = 0; B = 0; Cin = 0; #5
        A = 1; B = 0; Cin = 0; #5
        A = 0; B = 1; Cin = 0; #5
        A = 1; B = 1; Cin = 0; #5
        A = 0; B = 0; Cin = 1; #5
        A = 1; B = 0; Cin = 1; #5
        A = 0; B = 1; Cin = 1; #5
        A = 1; B = 1; Cin = 1; #5
        $finish;
     end   

endmodule
