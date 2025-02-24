`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/23/2025 08:14:25 PM
// Design Name: 
// Module Name: priorityEncoder
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


module priorityEncoder(
    input [7:0] x,
    output reg [2:0] y
    );
    
    always @(*) begin
        casez (x)
            8'b1??????? : y = 3'b111;
            8'b01?????? : y = 3'b110;
            8'b001????? : y = 3'b101;
            8'b0001???? : y = 3'b100;
            8'b00001??? : y = 3'b011;
            8'b000001?? : y = 3'b010;
            8'b0000001? : y = 3'b001;
            8'b00000001 : y = 3'b000;
            default : y = 3'b000;
        endcase
     end   
endmodule
