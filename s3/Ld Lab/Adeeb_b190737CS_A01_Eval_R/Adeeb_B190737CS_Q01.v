module circuitl (out, input_a, input_b, s);

    output[15:0] out;
    input[15:0]  input_a, input_b;
    input s;
    wire [15:0] a_not, b_not, w_and, w_nor, w_nand, w_nxor, w_xor, w_xor_not, w_or, w_or_not,w_xnor_not;
    wire s_not;

    not_gate_16 na1(a_not, input_a);
    not_gate_16 na2(b_not , input_b);   
    not_gate n1(s_not, s);

    and_gate_16 an1(w_and, input_a, input_b);
    nand nn1[15:0](w_nand, a_not, b_not);
    xnor_gate xnr1[15:0](w_xnor, a_not, b_not);
    nor_gate nr[15:0](w_nor, input_a, input_b);

    not_gate_16 n3(w_xnor_not,w_xnor);

    or_gate_16 oor1(w_or,w_and,w_nand);
    xor_gate_16 x5r(w_xor, w_xnor_not, w_nor);

    not_gate_16 n4(w_xor_not, w_xor);
    not_gate_16 n5(w_or_not, w_or);

    mux_16_2x1 mux1(out,w_or_not,w_xor_not,s);


endmodule