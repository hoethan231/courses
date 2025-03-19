`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/18/2025 10:09:53 PM
// Design Name: 
// Module Name: gray_code
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


module gray_code(
    input reset, clk,
    output reg [2:0] code
    );
    reg [2:0] next;
    
    always@(posedge clk, posedge reset) begin
        if (reset)
            code <= 3'b000;
        else 
            code <= next;
        end
        
    always@(*) begin
        case(code)
            3'b000: next = 3'b001;
            3'b001: next = 3'b011;
            3'b011: next = 3'b010;
            3'b010: next = 3'b110;
            3'b110: next = 3'b111;
            3'b111: next = 3'b101;
            3'b101: next = 3'b100;
            3'b100: next = 3'b000;
            default: next = 3'b000;
         endcase
     end
    
endmodule
