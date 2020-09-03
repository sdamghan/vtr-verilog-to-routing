module signed_arithmetic_left_shift_const (
				input  signed  [7:0]	   signed_a,
                                output [3:0] signed_left_shift
                           );

    assign    signed_left_shift  =   signed_a <<< 2;

endmodule
