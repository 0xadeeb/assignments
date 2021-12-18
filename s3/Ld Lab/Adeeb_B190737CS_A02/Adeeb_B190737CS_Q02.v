module full_adder(s,c_out,a,b,c_in);

    input a,b,c_in;
    output s,c_out;
    wire x_wire, a_wire ,f_wire;

    xor_gate x1(x_wire,a,b);
    xor_gate x2(s,c_in,x_wire);
    and_gate a1(f_wire,x_wire,c_in);
    and_gate a2(a_wire,a,b);
    or_gate o1(c_out, f_wire, a_wire );

endmodule
