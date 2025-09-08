`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2025 09:19:46 AM
// Design Name: 
// Module Name: tb_factorial_program
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

module tb_factorial_program;

  reg         clk;
  reg         rst;
  reg         go;
  reg  [31:0] n;
  wire        done;
  wire        error;
  wire [31:0] Q;

  factorial_program dut (
    .clk  (clk),
    .rst  (rst),
    .go   (go),
    .n    (n),
    .done (done),
    .error(error),
    .Q    (Q)
  );

  initial clk = 0;
  always #5 clk = ~clk;

  task fact32;
    input  [31:0] x;
    output [31:0] result;
    output        overflow;
    reg [63:0] acc;
    integer i;
    begin
      overflow = 0;
      acc      = 64'd1;
      if (x == 0) result = 32'd1;
      else begin
        for (i = 1; (i <= x) && (overflow == 0); i = i + 1) begin
          acc = acc * i;
          if (acc > 64'hFFFF_FFFF) overflow = 1;
        end
        result = acc[31:0];
      end
    end
  endtask

  task run_case;
    input [31:0] n_val;
    integer cycles;
    reg     exp_overflow;
    reg [31:0] exp_q;
    begin
      fact32(n_val, exp_q, exp_overflow);

      @(negedge clk);
      n  <= n_val;
      go <= 1'b1;
      @(negedge clk);
      go <= 1'b0;

      cycles = 0;
      while (!done && !error) begin
        @(negedge clk);
        cycles = cycles + 1;
        if (cycles > 5000) begin
          $display("TIMEOUT: n=%0d no done/error within limit.", n_val);
          $finish;
        end
      end

      if (exp_overflow) begin
        if (!error)
          $display("FAIL: n=%0d expected error=1 (overflow), got error=0", n_val);
        else
          $display("PASS (overflow): n=%0d -> error=1", n_val);
      end else begin
        if (error)
          $display("FAIL: n=%0d expected no error, but error=1", n_val);
        else if (Q !== exp_q)
          $display("FAIL: n=%0d expected Q=%0d got Q=%0d", n_val, exp_q, Q);
        else
          $display("PASS: n=%0d -> Q=%0d", n_val, Q);
      end

      repeat (2) @(negedge clk);
    end
  endtask

  initial begin
    rst = 1'b1; go = 1'b0; n = 32'd0;
    repeat (3) @(negedge clk);
    rst = 1'b0;

    run_case(32'd0);
    run_case(32'd1);
    run_case(32'd2);
    run_case(32'd3);
    run_case(32'd5);
    run_case(32'd10);
    run_case(32'd12);
    run_case(32'd13);
    run_case(32'd20); 

    $display("All testcases completed.");
    $finish;
  end

endmodule
`timescale 1ns/1ps

module tb_factorial_program;

  reg         clk;
  reg         rst;
  reg         go;
  reg  [31:0] n;
  wire        done;
  wire        error;
  wire [31:0] Q;

  factorial_program dut (
    .clk  (clk),
    .rst  (rst),
    .go   (go),
    .n    (n),
    .done (done),
    .error(error),
    .Q    (Q)
  );

  initial clk = 0;
  always #5 clk = ~clk;

  task fact32;
    input  [31:0] x;
    output [31:0] result;
    output        overflow;
    reg [63:0] acc;
    integer i;
    begin
      overflow = 0;
      acc      = 64'd1;
      if (x == 0) result = 32'd1;
      else begin
        for (i = 1; (i <= x) && (overflow == 0); i = i + 1) begin
          acc = acc * i;
          if (acc > 64'hFFFF_FFFF) overflow = 1;
        end
        result = acc[31:0];
      end
    end
  endtask

  task run_case;
    input [31:0] n_val;
    integer cycles;
    reg     exp_overflow;
    reg [31:0] exp_q;
    begin
      fact32(n_val, exp_q, exp_overflow);

      @(negedge clk);
      n  <= n_val;
      go <= 1'b1;
      @(negedge clk);
      go <= 1'b0;

      cycles = 0;
      while (!done && !error) begin
        @(negedge clk);
        cycles = cycles + 1;
        if (cycles > 5000) begin
          $display("TIMEOUT: n=%0d no done/error within limit.", n_val);
          $finish;
        end
      end

      if (exp_overflow) begin
        if (!error)
          $display("FAIL: n=%0d expected error=1 (overflow), got error=0", n_val);
        else
          $display("PASS (overflow): n=%0d -> error=1", n_val);
      end else begin
        if (error)
          $display("FAIL: n=%0d expected no error, but error=1", n_val);
        else if (Q !== exp_q)
          $display("FAIL: n=%0d expected Q=%0d got Q=%0d", n_val, exp_q, Q);
        else
          $display("PASS: n=%0d -> Q=%0d", n_val, Q);
      end

      repeat (2) @(negedge clk);
    end
  endtask

  initial begin
    rst = 1'b1; go = 1'b0; n = 32'd0;
    repeat (3) @(negedge clk);
    rst = 1'b0;

    run_case(32'd0);
    run_case(32'd1);
    run_case(32'd2);
    run_case(32'd3);
    run_case(32'd5);
    run_case(32'd10);
    run_case(32'd12);
    run_case(32'd13);
    run_case(32'd20);

    $display("All testcases completed.");
    $finish;
  end

endmodule