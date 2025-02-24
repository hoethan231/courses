`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/23/2025 09:08:43 PM
// Design Name: 
// Module Name: decoderTB
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


module decoderTB();
reg [1:0] x;
wire [3:0] y;

    decoder I(.x(x), .y(y));
    initial begin
        x = 2'b00; #5
        x = 2'b01; #5
        x = 2'b10; #5
        x = 2'b11; #5
        $finish();
    end
endmodule
