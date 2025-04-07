module three_bit_counter (
    input clk,
    input reset,
    output reg [2:0] count
);

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            count <= 3'b000;
        end else begin
            case (count)
                3'b000: count <= 3'b010;
                3'b010: count <= 3'b100;
                3'b100: count <= 3'b110;
                3'b110: count <= 3'b000;
                default: count <= 3'b000;
            endcase
        end
    end

endmodule

Test bench:
module three_bit_counter_tb;

    reg clk;
    reg reset;
    wire [2:0] count;

    three_bit_counter uut (
        .clk(clk),
        .reset(reset),
        .count(count)
    );

    always #5 clk = ~clk;

    initial begin
        clk = 0;
        reset = 1;

        #10 reset = 0;

        #100 $finish;
    end


endmodule




5.60
module counter (
    input clock,
    input en,
    output reg [3:0] count
);

    always @(posedge clock) begin
        if (en) begin
            if (count < 9)
                count <= count + 1;
            else
                count <= 0;
        end
    end

endmodule

Test bench:
module testbench;

    reg clk, en;
    wire [3:0] count;

    counter C1 (
        .clock(clk),
        .en(en),
        .count(count)
    );

    initial begin
        clk = 0;
        forever #1 clk = ~clk;
    end

    initial begin
        en = 1;
        #6 en = 0;
        #2 en = 1; 
    end

    initial begin
        #30 $finish; 
    end

endmodule