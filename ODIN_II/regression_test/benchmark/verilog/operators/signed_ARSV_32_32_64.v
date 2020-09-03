module signed_arithmetic_right_shift_variable (
				input [7:0]	shift,
				input  signed  [31:0]	   signed_a,
                                output signed [63:0] signed_right_shift
                           );

    assign    signed_right_shift =   signed_a >>> shift[5:0];

endmodule
