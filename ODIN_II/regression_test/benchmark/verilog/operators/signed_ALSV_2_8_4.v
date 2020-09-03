module signed_arithmetic_left_shift_variable (
				input [3:0]	shift,
				input  signed  [7:0]	   signed_a,
                                output signed [3:0] signed_left_shift 
                           );

   assign     signed_left_shift  =   signed_a <<< shift[2:1];

endmodule
