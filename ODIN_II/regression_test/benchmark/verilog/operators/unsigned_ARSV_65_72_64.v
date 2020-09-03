module unsigned_arithmetic_right_shift_variable (
				input [15:0]	shift,
				input   [71:0]	   unsigned_a,
                                output [63:0] unsigned_right_shift
                           );

    assign    unsigned_right_shift =   unsigned_a >>> shift[8:0];

endmodule
