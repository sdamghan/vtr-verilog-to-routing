module logical_left_shift_const (
				input    [31:0]	   a,
                                output [63:0] left_shift
                           );

    assign    left_shift  =   a << 32;

endmodule
