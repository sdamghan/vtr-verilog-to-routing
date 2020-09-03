module logical_right_shift_const (
				input    [7:0]	   a,
                                output [3:0] right_shift
                           );

   assign     right_shift =   a >> 2;

endmodule
