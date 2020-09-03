module unsigned_arithmetic_left_shift_const (
				input   [63:0]	   unsigned_a,
                                output [63:0] unsigned_left_shift
                           );

    assign    unsigned_left_shift  =   unsigned_a <<< 32;

endmodule
