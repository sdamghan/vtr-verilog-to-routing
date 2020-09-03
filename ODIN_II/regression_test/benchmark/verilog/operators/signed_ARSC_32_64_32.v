module signed_arithmetic_right_shift_const (
				input  signed  [63:0]	   signed_a,
                                output [32:0] signed_right_shift
                           );

    assign    signed_right_shift =   signed_a >>> 32;

endmodule
