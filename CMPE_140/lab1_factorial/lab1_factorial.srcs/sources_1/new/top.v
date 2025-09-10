module top(
input clk,
input rst,
input HILO_sel,
input [3:0] sw,
input go,
output [3:0] LEDSEL,
output [6:0] LEDOUT
);

wire clk_5kHz;
wire [3:0] dig0, dig1, dig2, dig3, dig4, dig5, dig6, dig7;
wire [3:0] HEX3, HEX2, HEX1, HEX0;
wire [6:0] LED3, LED2, LED1, LED0;
wire [31:0] switch_val = {28'b0, sw};
reg [31:0] result_reg;
wire [31:0] Q;

factorial_program(.n(switch_val), .clk(clk),.rst(rst), .go(go), .done(done), .error(error), .Q(Q));

always @ (posedge clk, posedge rst) begin
    if (rst) begin
        result_reg <= 32'b0;
    end
    if (done) begin
        result_reg <= Q;
    end
end

clk_gen U0 (
.clk50MHz(clk),
.rst(rst),
.clk_5KHz(clk_5kHz)
);
bin2hex32 U1(
.value(result_reg),
.dig0(dig0),
.dig1(dig1),
.dig2(dig2),
.dig3(dig3),
.dig4(dig4),
.dig5(dig5),
.dig6(dig6),
.dig7(dig7)
);
HILO_MUX DUT(
.HI_dig3(dig7),
.HI_dig2(dig6),
.HI_dig1(dig5),
.HI_dig0(dig4),
.LO_dig3(dig3),
.LO_dig2(dig2),
.LO_dig1(dig1),
.LO_dig0(dig0),
.HILO_sel(HILO_sel),
.HW_dig3(HEX3),
.HW_dig2(HEX2),
.HW_dig1(HEX1),
.HW_dig0(HEX0)
);
hex2led U_LD_3(
.number(HEX3),
.s0(LED3[0]),
.s1(LED3[1]),
.s2(LED3[2]),
.s3(LED3[3]),
.s4(LED3[4]),
.s5(LED3[5]),
.s6(LED3[6])
);
hex2led U_LD_2(
.number(HEX2),
.s0(LED2[0]),
.s1(LED2[1]),
.s2(LED2[2]),
.s3(LED2[3]),
.s4(LED2[4]),
.s5(LED2[5]),
.s6(LED2[6])
);
hex2led U_LD_1(
.number(HEX1),
.s0(LED1[0]),
.s1(LED1[1]),
.s2(LED1[2]),
.s3(LED1[3]),
.s4(LED1[4]),
.s5(LED1[5]),
.s6(LED1[6])
);
hex2led U_LD_0(
.number(HEX0),
.s0(LED0[0]),
.s1(LED0[1]),
.s2(LED0[2]),
.s3(LED0[3]),
.s4(LED0[4]),
.s5(LED0[5]),
.s6(LED0[6])
);
LED_MUX U3(
.clk(clk_5kHz),
.rst(rst),
.LED0(LED0),
.LED1(LED1),
.LED2(LED2),
.LED3(LED3),
.LEDOUT(LEDOUT),
.LEDSEL(LEDSEL));
endmodule