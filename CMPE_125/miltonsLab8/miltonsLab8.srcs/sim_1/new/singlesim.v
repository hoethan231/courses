`timescale 1ns/1ps

// -------------------------------------------------------------
// Testbench for the single_port RAM controller
// -------------------------------------------------------------
module single_port_tb;

  // -----------------------------------------------------------------
  // Parameterisation must match the DUT
  // -----------------------------------------------------------------
  parameter ADDRESS_WIDTH = 5;
  parameter DATA_WIDTH    = 32;

  // -----------------------------------------------------------------
  // Stimulus + monitor signals
  // -----------------------------------------------------------------
  reg  [ADDRESS_WIDTH-1:0] a, b, c;
  reg  [DATA_WIDTH-1:0]    w;
  reg                      clk, we;
  wire [DATA_WIDTH-1:0]    rd1;

  // -----------------------------------------------------------------
  // Instantiate the DUT
  // -----------------------------------------------------------------
  single_port #(
    .ADDRESS_WIDTH(ADDRESS_WIDTH),
    .DATA_WIDTH   (DATA_WIDTH   )
  ) dut (
    .a   (a  ),
    .b   (b  ),
    .c   (c  ),
    .w   (w  ),
    .clk (clk),
    .we  (we ),
    .rd1 (rd1)
  );

  // -----------------------------------------------------------------
  // 100 MHz free-running clock (10 ns period)
  // -----------------------------------------------------------------
  initial begin
    clk = 0;
    forever #5 clk = ~clk;
  end

  // -----------------------------------------------------------------
  // Vector-file driven stimulus
  // -----------------------------------------------------------------
  integer vec_fd;          // file descriptor
  integer rc;              // fscanf return code

  reg [ADDRESS_WIDTH-1:0] av, bv, cv;
  reg [DATA_WIDTH-1:0]    wv, exp_rd1;
  reg                     wev;

  initial begin
    // Reset all drive signals
    {a, b, c, w, we} = 0;

    // Open the vector file -- make sure it is next to the testbench
    vec_fd = $fopen("C:/Users/Admin/OneDrive/Desktop/Vs/School/CMPE_125/lab8/lab8.srcs/sim_1/new/testvector.tv", "r");
    if (vec_fd == 0) begin
      $display("ERROR: could not open test_vectors.txt");
      $finish;
    end

    // Skip the header line (anything that doesn't match the format is ignored)

    // -----------------------------------------------------------------
    // Main stimulus loop - one line per clock cycle
    // -----------------------------------------------------------------
    while (!$feof(vec_fd)) begin
      // Read one set of values from the file.
      // NOTE: Addresses and data are read as hex; WE is read as a single bit
      rc = $fscanf(vec_fd, "%h %h %h %h %b %h\n", av, bv, cv, wv, wev, exp_rd1);

      // Drive them on the next negative edge so the positive edge captures them
      @(negedge clk);
      a  <= av;
      b  <= bv;
      c  <= cv;
      w  <= wv;
      we <= wev;

      // Allow the DUT a positive edge to respond, then check the result
      @(posedge clk);
      #1;    // small delta-delay to allow rd1 to settle

      if (exp_rd1 !== 32'hX) begin
        if (rd1 !== exp_rd1) begin
          $display("[FAIL] %0t - exp: %h  got: %h", $time, exp_rd1, rd1);
        end else begin
          $display("[PASS] %0t - rd1 matched %h", $time, rd1);
        end
      end
    end

    $display("All vectors processed - simulation finished");
    $fclose(vec_fd);
    $stop;
  end

endmodule