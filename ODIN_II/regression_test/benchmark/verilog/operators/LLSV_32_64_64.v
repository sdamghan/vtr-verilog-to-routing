module logical_left_shift_variable (
				input    [63:0]	   a,
				input    [7:0]	   shift,
                                output [63:0] left_shift
                           );


    assign    left_shift  =   a << shift[5:0];

endmodule
