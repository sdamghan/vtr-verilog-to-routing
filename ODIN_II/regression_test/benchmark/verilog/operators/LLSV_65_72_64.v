module logical_left_shift_variable (
				input [15:0]	shift,
				input   [71:0]	   unsigned_a,
                                output [63:0] unsigned_left_shift
                           );


    assign    unsigned_left_shift  =   unsigned_a << shift[8:0];

endmodule
