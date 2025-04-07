`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/09/2024 11:05:29 AM
// Design Name: 
// Module Name: one_to_two_demultiplexer
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


module one_to_two_demultiplexer(
    input C,
    input select,
    output A,
    output B
    );

    not(selectn, select);
    and(B, C, selectn);
    and(A, C, select);

endmodule
