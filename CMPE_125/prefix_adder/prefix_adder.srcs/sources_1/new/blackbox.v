`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/19/2025 03:48:22 PM
// Design Name: 
// Module Name: blackbox
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


module blackbox(
    input [7:0] pik, gik, pkj, gkj,
    output [7:0] pij, gij
    );
    
    assign pij = pik & pkj;
    assign gij = gik | (pik & gkj);

endmodule
