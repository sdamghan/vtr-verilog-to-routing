module simple_op(
    clk,
    reset,
    a,
    out,
    clk_out
    );

    input   clk;
    input   reset;
    input signed  [2:0] a;

    output  [2:0]out;
    output  clk_out;

    assign clk_out = clk;

    always @(posedge clk)
    begin
        case(reset)
            0:       out <= a >>> 1;
            default:    out <= 0;
        endcase
    end
endmodule
