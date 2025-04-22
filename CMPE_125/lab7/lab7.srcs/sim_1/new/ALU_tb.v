`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/21/2025 09:31:40 PM
// Design Name: 
// Module Name: ALU_tb
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


module ALU_tb();
    
    reg [31:0] a, b;
    reg [2:0] F;
    wire [31:0] c;
    wire ZR, OV;

    ALU dut(.a(a), .b(b), .F(F), .c(c), .OV(OV), .ZR(ZR));
    
    initial begin
        
        // Test all basic functionality of ALU
        a = 32'b0000_0000_0000_0000_0000_0000_0000_1001; b = 32'b0000_0000_0000_0000_0000_0000_0000_0110;
        F = 3'b000; #5; // AND
        F = 3'b001; #5; // OR
        F = 3'b010; #5; // ADD
        F = 3'b100; #5;
        F = 3'b101; #5;
        F = 3'b110; #5; // SUB
        F = 3'b111; #5;
        
        // Endcases
        F = 3'b011; #5; // Not used
        a = 32'b0100_0000_0000_0000_0000_0000_0000_0000; b = 32'b0100_0000_0000_0000_0000_0000_0000_0000;
        F = 3'b010; #5; // Overflow
        $finish();
        end
endmodule
