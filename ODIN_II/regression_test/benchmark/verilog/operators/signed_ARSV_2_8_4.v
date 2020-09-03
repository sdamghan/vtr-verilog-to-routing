module signed_arithmetic_right_shift_variable (
				input [3:0]	shift,
				input  signed  [7:0]	   signed_a,
                                output signed [3:0] signed_right_shift
                           );

   assign     signed_right_shift =   signed_a >>> shift[2:1];

endmodule
