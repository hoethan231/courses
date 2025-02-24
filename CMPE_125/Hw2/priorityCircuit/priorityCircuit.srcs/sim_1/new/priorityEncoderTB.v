`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/23/2025 08:23:12 PM
// Design Name: 
// Module Name: priorityEncoderTB
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


module priorityEncoderTB();
reg [7:0] x;
wire [2:0] y;

    priorityEncoder I(.x(x), .y(y));
    initial begin
        x = 8'b00000000; #5
        x = 8'b00000001; #5
        x = 8'b00000111; #5
        x = 8'b10000101; #5
        $finish();
     end
endmodule
