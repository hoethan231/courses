`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/02/2024 10:33:25 AM
// Design Name: 
// Module Name: testbench_lab4
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

module Multiplexer;

reg A, B, select;
wire out;

Multiplexer utt(
    .A(A),
    .B(B),
    .select(select),
    .out(out)
);

initial begin

    A = 0; B = 0; select = 0;
    #10;
    
    A = 0; B = 1; select = 0;
    #10;
    
    A = 1; B = 0; select = 0;
    #10;
    
    A = 1; B = 1; select = 0;
    #10;    
    
    A = 0; B = 0; select = 1;
    #10;
    
    A = 0; B = 1; select = 1;
    #10;
    
    A = 1; B = 0; select = 1;
    #10;
    
    A = 1; B = 1; select = 1;
    #10;    
    
    $finish;
end

initial begin $monitor("time=%0d, input1=%b, input2=%b,select line=%b, output=%b", $time, A, B, select, out);
end
endmodule
