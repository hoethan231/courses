`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/04/2025 11:51:43 AM
// Design Name: 
// Module Name: self_check_TB
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


module self_check_TB();

reg [3:0] a, b;
reg ci;
wire [3:0] s; 
wire co, pg, gg;

    CLA4 dut(.a(a), .b(b), .ci(ci), .s(s), .co(co), .pg(pg), .gg(gg));
    initial begin
        a = 4'b0000; b = 4'b1111; ci = 1; #10;
        if(s !== 4'b0000 | co !== 1 | pg !== 1 | gg != 0) $display("a = 4'b0000; b = 4'b1111; cin = 1; failed");
        a = 4'b0001; b = 4'b1000; ci = 1; #10;
        if(s !== 4'b1010 | co !== 0 | pg !== 0 | gg !== 0) $display("a = 4'b0001; b = 4'b1000; ci = 1; failed");
        a = 4'b0010; b = 4'b1110; ci = 1; #10;
        if(s !== 4'b0001 | co !== 1 | pg !== 0 | gg !== 1) $display("a = 4'b0010; b = 4'b1110; cin = 1; failed");
        a = 4'b0011; b = 4'b1100; ci = 0; #10;
        if(s !== 4'b1111 | co !== 0 | pg !== 1 | gg !== 0) $display("a = 4'b0011; b = 4'b1100; ci = 0; failed");
    $finish();
    end
endmodule



