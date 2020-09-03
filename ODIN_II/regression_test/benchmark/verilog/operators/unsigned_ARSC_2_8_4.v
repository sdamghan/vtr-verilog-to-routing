module unsigned_arithmetic_right_shift_const (
				input   [7:0]	   unsigned_a,
                                output [3:0] unsigned_right_shift
                           );


    assign    unsigned_right_shift =   unsigned_a >>> 2;

endmodule
