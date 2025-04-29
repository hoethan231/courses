`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/28/2025 06:31:00 PM
// Design Name: 
// Module Name: dualPortRAM
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


module dualPortRAM(
    input wea, web, clkA, clkB,
    input [5:0] a, b,
    input [31:0] wda, wdb,
    output [31:0] rda, rdb
    );
    reg [31:0] mem [31:0];

    always @(posedge clkA) begin
        if (wea) mem[a] = wda;
    end
    
    always @(posedge clkB) begin    
        if (web) mem[b] = wdb;      
    end                             
    
    assign rda = mem[a];
    assign rdb = mem[b];
endmodule
