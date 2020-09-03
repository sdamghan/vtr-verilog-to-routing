module logical_left_shift_const (
				input    [7:0]	   a,
                                output [3:0] left_shift
                           );

   assign     left_shift  =   a << 2;

endmodule
