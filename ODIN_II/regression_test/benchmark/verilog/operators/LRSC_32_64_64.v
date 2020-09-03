module logical_right_shift_const (
				input    [63:0]	   a,
                                output [63:0] right_shift
                           );

    assign    right_shift =   a >> 32;

endmodule
