`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/06/2025 02:20:25 PM
// Design Name: 
// Module Name: control_unit
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


module control_unit(
    input clk, GO, Error, GT,
    output reg SEL, load_reg, load_cnt, OE, EN, done, error
    );
    
    reg [2:0] curr, next;
    parameter s0 = 3'b000;
    parameter s1 = 3'b001;
    parameter s2 = 3'b010;
    parameter s3 = 3'b011;
    parameter s4 = 3'b100;
    
    always @ (posedge clk) begin
        curr <= next;
    end
    
    always @ (*) begin
        case (curr)
            s0: begin
                load_reg = 0;
                load_cnt = 0;
                SEL = 0;
                EN = 0;
                OE = 0;
                error = 0;
                done = 0;
                if (GO) next = s1;
                else next = s0;
            end
            s1: begin
                if (!Error) begin
                    load_reg = 1;
                    load_cnt = 1;
                    next = s2;
                end
                else begin
                    error = 1;
                    next = s0;
                end
            end
            s2: begin
                if (GT) begin
                    load_reg = 0;
                    EN = 0;
                    SEL = 1;
                    next = s3;
                end
                else begin
                    next = s4;
                end
            end
            s3: begin
                load_reg = 1;
                EN = 1;
                next = s2;
            end
            s4: begin
                OE = 1;
                done = 1;
            end
        endcase
    end
    
endmodule
