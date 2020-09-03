module unsigned_arithmetic_right_shift_const (
				input   [63:0]	   unsigned_a,
                                output [32:0] unsigned_right_shift
                           );

    assign    unsigned_right_shift =   unsigned_a >>> 32;

endmodule
