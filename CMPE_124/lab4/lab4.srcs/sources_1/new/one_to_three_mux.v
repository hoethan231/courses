//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/09/2024 01:34:31 PM
// Design Name: 
// Module Name: one_to_three_mux
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

module one_to_three_mux(
    input C,
    input select0,
    input select1,
    output A,
    output B,
    output D
    );

    not(select0n, select0);
    not(select1n, select1);
    and(B, C, selectn);
    and(A, C, select);
    and(D, C, select0);
    
endmodule
