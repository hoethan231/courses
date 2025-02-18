`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/18/2025 11:17:57 AM
// Design Name: 
// Module Name: displayDecoderTB
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


module displayDecoderTB();
reg [3:0] SW;
wire [6:0] HEX0;

    displayDecoder I(.SW(SW), .HEX0(HEX0));
    initial begin
        SW = 4'b0000; #5
        SW = 4'b0001; #5
        SW = 4'b0010; #5
        SW = 4'b0011; #5
        SW = 4'b0100; #5
        SW = 4'b0101; #5
        SW = 4'b0110; #5
        SW = 4'b0111; #5
        SW = 4'b1000; #5
        SW = 4'b1001; #5
        SW = 4'b1010; #5
        SW = 4'b1011; #5
        SW = 4'b1100; #5
        SW = 4'b1101; #5
        SW = 4'b1110; #5
        SW = 4'b1111; #5
        $finish;
    end
endmodule
