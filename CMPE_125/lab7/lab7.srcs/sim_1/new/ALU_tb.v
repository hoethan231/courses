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
    wire ZR, OV, CF;

    integer fd;
    integer status;
    reg [66:0] line_bits;

    ALU dut(.a(a), .b(b), .F(F), .c(c), .OV(OV), .ZR(ZR), .CF(CF));
    
    initial begin
        fd = $fopen("C:/Users/Admin/OneDrive/Desktop/Vs/School/CMPE_125/lab7/lab7.srcs/sim_1/new/testvector.tv", "r");
        if (fd == 0) begin
            $display("Error: could not open file");
            $finish;
        end

        a = 32'b0; b = 32'b0; F = 3'b0; #5;
    
        while (!$feof(fd)) begin
            status = $fscanf(fd, "%b\n", line_bits);
            if (status == 1) begin
                a = line_bits[66:35];
                b = line_bits[34:3];
                F = line_bits[2:0];
                #10;
            end
        end
      $fclose(fd);
      $display("simulation done");
      $finish;
    end
endmodule
