`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/08/2025 10:35:48 AM
// Design Name: 
// Module Name: vendingmachine_tb
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


module vendingmachine_tb();
    reg clk, reset;
    reg N, D, Q;
    
    wire [3:0] out; 
    
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    integer fd;
    integer status;

    reg [7:0] line_bits;
    reg [3:0] expected;

    vendingmachine dut(.clk(clk), .reset(reset), .N(N), .D(D), .Q(Q), .out(out));

    initial begin
        fd = $fopen("C:/Users/Admin/OneDrive/Desktop/Vs/School/CMPE_125/lab6/lab6.srcs/sim_1/new/testvector.tv", "r");
        if (fd == 0) begin
        $display("Error: could not open file");
        $finish;
    end

    reset = 0;
    N = 0; D = 0; Q = 0;

    #15;
    while (!$feof(fd)) begin
        status = $fscanf(fd, "%b\n", line_bits);
        if (status == 1) begin
        reset = line_bits[7];
        N     = line_bits[6];
        D     = line_bits[5];
        Q     = line_bits[4];

        expected = line_bits[3:0];

      @(posedge clk);

        if (out != expected) begin
            $display("Time %0t: Mismatch", $time);
            $display("  Inputs: reset = %b, n = %b, d = %b, q = %b", reset, N, D, Q);
            $display("  Expected out = %b, result = %b", expected, out);
        end
        else begin
            $display("Time %0t: PASS (out = %b)", $time, out);
        end
    end
end
  $fclose(fd);
  $display("simulation done");
  $finish;
end

endmodule
