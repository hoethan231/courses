`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/09/2024 10:38:55 AM
// Design Name: 
// Module Name: three_in_one_mux_tb
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

module three_in_one_mux_tb;

reg A, B, C, select0, select1;
wire out;

three_in_one_mux utt(
    .A(A),
    .B(B),
    .C(C),
    .select0(select0),
    .select1(select1),
    .out(out)
);

initial begin

    A = 0; B = 0; C = 0; select0 = 0; select1 = 0;
    #10;
    A = 0; B = 0; C = 1; select0 = 0; select1 = 0;
    #10;
    A = 0; B = 1; C = 0; select0 = 0; select1 = 0;
    #10;
    A = 0; B = 1; C = 1; select0 = 0; select1 = 0;
    #10;
    A = 1; B = 0; C = 0; select0 = 0; select1 = 0;
    #10;
    A = 1; B = 0; C = 1; select0 = 0; select1 = 0;
    #10;
    A = 1; B = 1; C = 0; select0 = 0; select1 = 0;
    #10;
    A = 1; B = 1; C = 1; select0 = 0; select1 = 0;
    #10;    
    
    A = 0; B = 0; C = 0; select0 = 0; select1 = 1;
    #10;
    A = 0; B = 0; C = 1; select0 = 0; select1 = 1;
    #10;
    A = 0; B = 1; C = 0; select0 = 0; select1 = 1;
    #10;
    A = 0; B = 1; C = 1; select0 = 0; select1 = 1;
    #10;
    A = 1; B = 0; C = 0; select0 = 0; select1 = 1;
    #10;
    A = 1; B = 0; C = 1; select0 = 0; select1 = 1;
    #10;
    A = 1; B = 1; C = 0; select0 = 0; select1 = 1;
    #10;
    A = 1; B = 1; C = 1; select0 = 0; select1 = 1;
    #10;    
    
    A = 0; B = 0; C = 0; select0 = 1; select1 = 0;
    #10;
    A = 0; B = 0; C = 1; select0 = 1; select1 = 0;
    #10;
    A = 0; B = 1; C = 0; select0 = 1; select1 = 0;
    #10;
    A = 0; B = 1; C = 1; select0 = 1; select1 = 0;
    #10;
    A = 1; B = 0; C = 0; select0 = 1; select1 = 0;
    #10;
    A = 1; B = 0; C = 1; select0 = 1; select1 = 0;
    #10;
    A = 1; B = 1; C = 0; select0 = 1; select1 = 0;
    #10;
    A = 1; B = 1; C = 1; select0 = 1; select1 = 0;
    #10;    
    
    A = 0; B = 0; C = 0; select0 = 1; select1 = 1;
    #10;
    A = 0; B = 0; C = 1; select0 = 1; select1 = 1;
    #10;
    A = 0; B = 1; C = 0; select0 = 1; select1 = 1;
    #10;
    A = 0; B = 1; C = 1; select0 = 1; select1 = 1;
    #10;
    A = 1; B = 0; C = 0; select0 = 1; select1 = 1;
    #10;
    A = 1; B = 0; C = 1; select0 = 1; select1 = 1;
    #10;
    A = 1; B = 1; C = 0; select0 = 1; select1 = 1;
    #10;
    A = 1; B = 1; C = 1; select0 = 1; select1 = 1;
    #10;    
    
    
    $finish;
end

endmodule

