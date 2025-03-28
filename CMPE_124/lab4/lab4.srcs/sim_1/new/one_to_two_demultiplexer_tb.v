`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/09/2024 11:27:01 AM
// Design Name: 
// Module Name: one_to_two_demultiplexer_tb
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

module one_to_two_demultiplexer_tb;

reg C, select;
wire A, B;

one_to_two_demultiplexer utt(
    .A(A),
    .B(B),
    .C(C),
    .select(select)
);

initial begin

    C = 0; select = 0;
    #10;
    C = 0; select = 1;
    #10;
    C = 1; select = 0;
    #10;
    C = 1; select = 1;

    #10;    
 
    $finish;
end

endmodule
