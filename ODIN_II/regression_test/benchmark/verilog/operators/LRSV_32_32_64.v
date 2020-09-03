module logical_right_shift_variable (
				input    [31:0]	   a,
				input    [7:0]	   shift,
                                output [63:0] right_shift
                           );

    assign    right_shift =   a >> shift[5:0];

endmodule
