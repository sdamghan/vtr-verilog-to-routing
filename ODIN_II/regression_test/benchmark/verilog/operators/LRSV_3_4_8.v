module logical_right_shift_variable (
				input    [3:0]	   a,
				input    [2:0]	   shift,
                                output [7:0] right_shift
                           );

   assign     right_shift =   a >> shift[2:1];

endmodule
