`define N_ADDER 4
`define N_BIT 128

module simple_op(
    a_1,
    b_1,    
    out_1,
    a_2,
    b_2,    
    out_2,
    a_3,
    b_3,    
    out_3,
    a_4,
    b_4,    
    out_4,
    );

    input   [`N_BIT-1:0]a_1;
    input   [`N_BIT-1:0]b_1;
    output  [`N_BIT-1:0]out_1;


    input   [`N_BIT-1:0]a_2;
    input   [`N_BIT-1:0]b_2;
    output  [`N_BIT-1:0]out_2;

    input   [`N_BIT-1:0]a_3;
    input   [`N_BIT-1:0]b_3;
    output  [`N_BIT-1:0]out_3;

    input   [`N_BIT-1:0]a_4;
    input   [`N_BIT-1:0]b_4;
    output  [`N_BIT-1:0]out_4;

            assign out_1 = a_1 + b_1;
            assign out_2 = a_2 + b_2;
            assign out_3 = a_3 + b_3;
            assign out_4 = a_4 + b_4;

endmodule