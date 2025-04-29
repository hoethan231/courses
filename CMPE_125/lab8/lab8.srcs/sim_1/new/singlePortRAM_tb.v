`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/28/2025 07:26:47 PM
// Design Name: 
// Module Name: singlePortRAM_tb
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


module singlePortRAM_tb();
    
    reg [5:0] a;
    reg wea, clkA;
    reg [31:0] wda;
    wire [31:0] rda;

    integer fd;
    integer status;
    reg [70:0] line_bits;
    reg [31:0] expectedRDA;

    singlePortRAM dut(.a(a), .wea(wea), .clkA(clkA), .wda(wda), .rda(rda));
    
    always #5 clkA = ~clkA;
    initial begin
        fd = $fopen("C:/Users/Admin/OneDrive/Desktop/Vs/School/CMPE_125/lab8/lab8.srcs/sim_1/new/testvector.tv", "r");
        if (fd == 0) begin
            $display("Error: could not open file");
            $finish;
        end

        a = 6'b0; wea = 1'b0; clkA = 0; wda = 32'b0; #5;
        
        while (!$feof(fd)) begin
            status = $fscanf(fd, "%b\n", line_bits);
            if (status == 1) begin
                a = line_bits[70:65];
                wea = line_bits[64];
                wda = line_bits[63:32];
                expectedRDA = line_bits[31:0];
                #10;
            end
        end
        
        @(posedge clkA);

        if (rda != expectedRDA) begin
            $display("Time %0t: Mismatch", $time);
            $display("  Expected out = %b, got = %b", expectedRDA, rda);
        end
        else begin
            $display("Time %0t: PASS (rda = %b)", $time, rda);
        end
      $fclose(fd);
      $display("simulation done");
      $finish;
    end
endmodule