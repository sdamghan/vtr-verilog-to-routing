module logical_left_shift_variable (
				input    [7:0]	   a,
				input    [2:0]	   shift,
                                output [7:0] left_shift
                           );


    assign    left_shift  =   a << shift[2:1];

endmodule
