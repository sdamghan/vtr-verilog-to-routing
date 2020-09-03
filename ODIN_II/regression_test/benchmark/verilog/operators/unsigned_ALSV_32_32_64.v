module unsigned_arithmetic_left_shift_variable (
				input [7:0]	shift,
				input   [31:0]	   unsigned_a,
                                output [63:0] unsigned_left_shift
                           );

    assign    unsigned_left_shift  =   unsigned_a <<< shift[5:0];

endmodule
