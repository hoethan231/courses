//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/18/2024 02:47:28 PM
// Design Name: 
// Module Name: D_Flip_Flop_TB
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

module four_bit_counter (
    input wire clk,        // Clock input
    input wire reset,      // Active-low reset (Reset = 0 resets the counter)
    input wire count,      // Count input (1 = decrement, 0 = stall)
    output wire [3:0] q    // 4-bit counter output
);

    wire [3:0] subtractor_out; // Output of the Ripple Carry Subtractor
    wire [3:0] mux_out;        // Output of the 2-1 MUX
    wire borrow_out;           // Borrow-out from the RCS (not used)

    // Ripple Carry Subtractor (subtracts 1 from the counter output)
    ripple_carry_subtractor_4 RCS (
        .a(q),
        .b(4'b0001),           // Constant decrement value (1)
        .cin(1'b0),            // Borrow-in for the least significant bit
        .sum(subtractor_out),
        .cout(borrow_out)      // Unused
    );

    // Four 2-1 MUXes (choose between current value and subtractor output)
    generate
        genvar i;
        for (i = 0; i < 4; i = i + 1) begin : mux_gen
            assign mux_out[i] = (count) ? subtractor_out[i] : q[i];
        end
    endgenerate

    // Four D-type Flip-Flops (store the counter value)
    generate
        for (i = 0; i < 4; i = i + 1) begin : dff_gen
            d_flip_flop DFF (
                .clk(clk),
                .reset(reset),
                .d(mux_out[i]),
                .q(q[i])
            );
        end
    endgenerate

endmodule

// Ripple Carry Subtractor (4-bit)
module ripple_carry_subtractor_4 (
    input wire [3:0] a,   // First operand
    input wire [3:0] b,   // Second operand (subtrahend)
    input wire cin,       // Borrow-in
    output wire [3:0] sum, // Result output
    output wire cout       // Borrow-out
);
    wire [3:0] borrow; // Internal borrow wires
    wire [3:0] b_not;  // Two's complement of b

    // Invert each bit of b to perform subtraction
    assign b_not = ~b;

    // Instantiate full adders for subtraction
    full_adder FA0 (.a(a[0]), .b(b_not[0]), .cin(cin),     .sum(sum[0]), .cout(borrow[0]));
    full_adder FA1 (.a(a[1]), .b(b_not[1]), .cin(borrow[0]), .sum(sum[1]), .cout(borrow[1]));
    full_adder FA2 (.a(a[2]), .b(b_not[2]), .cin(borrow[1]), .sum(sum[2]), .cout(borrow[2]));
    full_adder FA3 (.a(a[3]), .b(b_not[3]), .cin(borrow[2]), .sum(sum[3]), .cout(cout));

endmodule

// Full Adder (1-bit)
module full_adder (
    input wire a,      // First operand bit
    input wire b,      // Second operand bit
    input wire cin,    // Carry-in
    output wire sum,   // Sum output
    output wire cout   // Carry-out
);
    assign sum = a ^ b ^ cin;
    assign cout = (a & b) | (b & cin) | (a & cin);
endmodule

// D-Type Flip-Flop
module d_flip_flop (
    input wire clk,        // Clock input
    input wire reset,      // Active-low reset
    input wire d,          // Data input
    output reg q           // Output
);
    always @(posedge clk or negedge reset) begin
        if (!reset)
            q <= 0;       // Reset the flip-flop
        else
            q <= d;       // Store the input value
    end
endmodule


