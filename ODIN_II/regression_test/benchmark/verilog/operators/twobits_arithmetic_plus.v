`define N_ADDER 4
`define N_BIT 8

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
    a_5,
    b_5,    
    out_5,
    a_6,
    b_6,    
    out_6
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

    input   [`N_BIT-1:0]a_5;
    input   [`N_BIT-1:0]b_5;
    output  [`N_BIT-1:0]out_5;

    input   [`N_BIT-1:0]a_6;
    input   [`N_BIT-1:0]b_6;
    output  [`N_BIT-1:0]out_6;

            assign out_1 = a_1 + b_1;
            assign out_2 = a_2 + b_2;
            assign out_3 = a_3 + b_3;
            assign out_4 = a_4 + b_4;
            assign out_5 = a_5 + b_5;
            assign out_6 = a_6 + b_6;


endmodule