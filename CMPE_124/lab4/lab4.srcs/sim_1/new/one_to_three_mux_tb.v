//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/09/2024 02:20:43 PM
// Design Name: 
// Module Name: one_to_three_mux_tb
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
`timescale 1ns/1ps

module one_to_three_mux_tb;

reg C, select0, select1;
wire A, B, D;

one_to_three_mux utt(
    .A(A),
    .B(B),
    .C(C),
    .D(D),
    .select0(select0),
    .select1(select1)
);

initial begin

    select0 = 0; select1 = 0; C = 0;
    #10;
    select0 = 0; select1 = 0; C = 1;
    #10;
    select0 = 0; select1 = 1; C = 0;
    #10;
    select0 = 0; select1 = 1; C = 1;
    #10;
    select0 = 1; select1 = 0; C = 0;
    #10;
    select0 = 1; select1 = 0; C = 1;
    #10;
    select0 = 1; select1 = 1; C = 0;
    #10;
    select0 = 1; select1 = 1; C = 1;
    #10;    
    
    $finish;
end

endmodule

