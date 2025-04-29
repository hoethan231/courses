`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/29/2025 11:23:46 AM
// Design Name: 
// Module Name: truePortRAM
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


module truePortRAM(                     
    input wea, web, clk,         
    input [5:0] a, b,                   
    input [31:0] wda, wdb,              
    output [31:0] rda, rdb              
    );                                  
    reg [31:0] mem [31:0];              
                                        
    always @(posedge clk) begin        
        if (wea) mem[a] = wda;    
        if (web) mem[b] = wdb;          
    end                                 
                                        
    assign rda = mem[a];                
    assign rdb = mem[b];                
endmodule                               
                                        
