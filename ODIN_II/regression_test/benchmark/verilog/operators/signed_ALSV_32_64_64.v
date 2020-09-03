module signed_arithmetic_left_shift_variable (
				input [7:0]	shift,
				input  signed  [63:0]	   signed_a,
                                output signed [63:0] signed_left_shift
                           );

    assign    signed_left_shift  =   signed_a <<< shift[5:0];

endmodule
