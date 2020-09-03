module logical_left_shift_const (
				input    [7:0]	   a,
                                output [7:0] left_shift
                           );

    assign    left_shift  =   a << 3;

endmodule
