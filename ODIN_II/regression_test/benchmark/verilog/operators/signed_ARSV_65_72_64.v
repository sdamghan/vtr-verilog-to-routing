module signed_arithmetic_right_shift_variable (
				input [15:0]	shift,
				input  signed  [71:0]	   signed_a,
                                output signed [63:0] signed_right_shift
                           );

    assign    signed_right_shift =   signed_a >>> shift[8:0];

endmodule
