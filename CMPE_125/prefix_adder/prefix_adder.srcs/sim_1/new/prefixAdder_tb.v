`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/19/2025 05:12:50 PM
// Design Name: 
// Module Name: prefixAdder_tb
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


module prefixAdder_tb();

reg [15:0] a, b;
reg cin;
wire [15:0] s;
wire cout;

integer fd;
integer status;

reg [49:0] line_bits;
reg [15:0] expectedS;
reg expectedCout;

prefixAdder uut(.a(a), .b(b), .cin(cin), .s(s), .cout(cout));
    
initial begin
        fd = $fopen("C:/Users/Admin/OneDrive/Desktop/Vs/School/CMPE_125/prefix_adder/prefix_adder.srcs/sim_1/new/testvector.tv", "r");
        if (fd == 0) begin
            $display("Error: could not open file");
            $finish;
        end

    a = 16'b0; b = 16'b0; cin = 0; #10;

    while (!$feof(fd)) begin
        status = $fscanf(fd, "%b\n", line_bits);
        if (status == 1) begin
            a = line_bits[49:34];
            b = line_bits[33:18];
            cin = line_bits[17];
            expectedS = line_bits[16:1];
            expectedCout = line_bits[0];
            
    
            #10;
    
            if (s != expectedS | cout != expectedCout) begin
                $display("Time %0t: Mismatch", $time);
                $display("  Inputs: a = %b, b = %b, cin = %b", a, b, cin);
                $display("  Expected s = %b, cout = %b", expectedS, expectedCout);
                $display("  Got s = %b, cout = %b", s, cout);
            end
            else begin
                $display("Time %0t: PASS (s = %b)", $time, s);
            end
        end
    end
  $fclose(fd);
  $display("simulation done");
  $finish;
end

endmodule
