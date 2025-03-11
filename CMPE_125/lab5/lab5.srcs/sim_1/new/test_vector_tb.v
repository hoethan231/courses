`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/04/2025 02:25:10 PM
// Design Name: 
// Module Name: test_vector_tb
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

module test_vector_tb();
    reg clk, reset;
    reg [3:0] a, b;
    reg ci;
    reg [3:0] expectedS; 
    reg expectedCO, expectedPG, expectedGG;
    
    reg [15:0] testvectors[10000:0];
    reg [31:0] vectornum, errors;
    
    wire [3:0] s; 
    wire co, pg, gg;
    
    CLA4 dut(.a(a), .b(b), .ci(ci), .s(s), .co(co), .pg(pg), .gg(gg));
    
    always begin
        clk = 1; #27; clk = 0; #5;
    end
    
    initial begin
        $readmemb("C:/Users/Admin/OneDrive/Desktop/Vs/School/CMPE_125/lab5/lab5.srcs/sim_1/new/test_vector.tv", testvectors);
        vectornum = 0; errors = 0;
        reset = 1; #5; reset = 0;
    end
    
    always @(posedge clk)
    begin
        if (~reset) begin
            #1; {a, b, ci, expectedS, expectedCO, expectedPG, expectedGG} = testvectors[vectornum];
        end
    end
    
    always @(negedge clk)
    if (~reset) begin
        if (s !== expectedS || co !== expectedCO || pg !== expectedPG || gg !== expectedGG) begin
            $display("Error at vector %d:", vectornum);
            $display("  Inputs: a=%b, b=%b, ci=%b", a, b, ci);
            $display("  Expected: s=%b, co=%b, pg=%b, gg=%b", expectedS, expectedCO, expectedPG, expectedGG);
            $display("  Got: s=%b, co=%b, pg=%b, gg=%b", s, co, pg, gg);
            errors = errors + 1;
        end
        
        vectornum = vectornum + 1;
        
        if (testvectors[vectornum] === 16'bx) begin
            $display("%d tests completed with %d errors", vectornum, errors);
            $finish();
        end
    end
endmodule



