`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/08/2025 10:15:54 AM
// Design Name: 
// Module Name: vendingmachine
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


module vendingmachine(
    input clk, reset, N, D, Q,
    output reg [3:0] out
    );
    
    reg [2:0] curr, next;
    
    parameter S0 = 3'b000;
    parameter S5 = 3'b001;
    parameter S10 = 3'b010;
    parameter S15 = 3'b011;
    parameter S20 = 3'b100;
    parameter S25 = 3'b101;
    
    always @ (posedge clk) begin
            curr <= next;
    end
        
    always @ (*) begin
        case (curr)
            S0:
                if (N) begin
                    next = S5;
                    out = 4'b0000;
                    end
                else if (D) begin
                    next = S10;
                    out = 4'b0000;
                    end
                else if (Q) begin
                    next = S0;
                    out = 4'b1000;
                    end
                else begin
                    next = S0;
                    out = 4'b0000;
                    end
            S5:
                if (N) begin
                    next = S10;
                    out = 4'b0000;
                    end
                else if (D) begin
                    next = S15;
                    out = 4'b0000;
                    end
                else if (Q) begin
                    next = S0;
                    out = 4'b1100;
                    end
                else begin
                    next = S0;
                    out = 4'b0100;
                    end
            S10:
                if (N) begin
                    next = S15;
                    out = 4'b0000;
                    end
                else if (D) begin
                    next = S20;
                    out = 4'b0000;
                    end
                else if (Q) begin
                    next = S0;
                    out = 4'b1010;
                    end
                else begin
                    next = S0;
                    out = 4'b0010;
                    end
            S15:
                if (N) begin
                    next = S20;
                    out = 4'b0000;
                    end
                else if (D) begin
                    next = S0;
                    out = 4'b1000;
                    end
                else if (Q) begin
                    next = S0;
                    out = 4'b1110;
                    end
                else begin
                    next = S0;
                    out = 4'b0110;
                    end
            S20:
                if (N) begin
                    next = S0;
                    out = 4'b1000;
                    end
                else if (D) begin
                    next = S0;
                    out = 4'b1100;
                    end
                else if (Q) begin
                    next = S0;
                    out = 4'b1001;
                    end
                else begin
                    next = S0;
                    out = 4'b0001;
                    end
             default: begin
                 next = S0;
                 out = 4'b0000;
                 end
             endcase
         end
endmodule