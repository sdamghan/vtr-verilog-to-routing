module signed_arithmetic_right_shift_const (
				input  signed  [71:0]	   signed_a,
                                output [63:0] signed_right_shift
                           );

    assign    signed_right_shift =   signed_a >>> 65;

endmodule
