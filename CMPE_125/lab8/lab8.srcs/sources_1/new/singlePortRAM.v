`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/28/2025 07:16:16 PM
// Design Name: 
// Module Name: singlePortRAM
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


module singlePortRAM(
    input wea, clkA,
    input [5:0] a,
    input [31:0] wda,
    output [31:0] rda
    );
    reg [31:0] mem [31:0];

    assign rda = mem[a];

    always @(posedge clkA) begin
        if (wea) mem[a] <= wda;
        end
endmodule
