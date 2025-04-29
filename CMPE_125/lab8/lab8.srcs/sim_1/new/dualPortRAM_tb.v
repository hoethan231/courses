`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/28/2025 11:02:04 PM
// Design Name: 
// Module Name: dualPortRAM_tb
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


module dualPortRAM_tb;

    reg         clkA = 0, clkB = 0;
    reg  [5:0]  a = 0, b = 0, c = 0;
    reg         wea = 0, web;
    reg  [31:0] wda = 0, wdb = 0;
    wire [31:0] rda, rdb;

    integer     fd, status;
    reg  [141:0] line_bits;
    reg  [31:0] expectedRDA, expectedRDB;

    always #5 clkA = ~clkA;
    always #5 clkB = ~clkB;

    dualPortRAM dut (
        .wea (wea), .web(web),
        .clkA(clkA), .clkB(clkB),
        .a  (a), .b(b),
        .wda (wda), .wdb(wdb),
        .rda(rda), .rdb(rdb)
    );

    initial begin
        fd = $fopen("C:/Users/Admin/OneDrive/Desktop/Vs/School/CMPE_125/lab8/lab8.srcs/sim_1/new/testvector2.tv", "r");
        if (fd == 0) begin
            $display("ERROR: can't open vector file"); $finish;
        end

        while (!$feof(fd)) begin
            status = $fscanf(fd, "%b\n", line_bits);
            if (status == 1) begin
                a           = line_bits[141:136]; 
                b           = line_bits[135:130];  
                wea         = line_bits[129];      
                web         = line_bits[128];       
                wda         = line_bits[127:96];    
                wdb         = line_bits[95:64];     
                expectedRDA = line_bits[63:32];     
                expectedRDB = line_bits[31:0];     
                #10;

                if (rda !== expectedRDA || rdb !== expectedRDB) begin
                    $display("FAIL @%0t  exp A=%h  B=%h   got A=%h  B=%h",
                             $time, expectedRDA, expectedRDB, rda, rdb);
                end
                else begin
                    $display("PASS @%0t  rda=%h  rdb=%h",
                             $time, rda, rdb);
                end
            end
        end
        $fclose(fd);
        $display("Simulation done."); $finish;
    end
endmodule

