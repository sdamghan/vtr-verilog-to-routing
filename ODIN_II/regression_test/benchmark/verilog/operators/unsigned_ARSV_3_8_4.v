module unsigned_arithmetic_right_shift_variable (
				input [3:0]	shift,
				input   [7:0]	   unsigned_a,
                                output [3:0] unsigned_right_shift
                           );

    assign    unsigned_right_shift =   unsigned_a >>> shift[2:1];

endmodule
