module logical_right_shift_const (
				input   [71:0]	   unsigned_a,
                                output [63:0] unsigned_right_shift
                           );

    assign    unsigned_right_shift =   unsigned_a >> 65;

endmodule
