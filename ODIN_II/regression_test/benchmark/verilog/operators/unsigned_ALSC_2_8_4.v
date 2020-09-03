module unsigned_arithmetic_left_shift_const (
				input   [7:0]	   unsigned_a,
                                output [3:0] unsigned_left_shift
                           );

    assign    unsigned_left_shift  =   unsigned_a <<< 2;

endmodule
