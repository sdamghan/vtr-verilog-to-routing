module signed_arithmetic_left_shift_const (
				input  signed  [71:0]	   signed_a,
                                output [63:0] signed_left_shift, 
                           );

    assign    signed_left_shift  =   signed_a <<< 65;

endmodule
