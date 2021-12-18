module mux_2x1(y,x0,x1,s0);

    output y;
    input x0,x1,s0;
    wire w1,w2,w0;

    not_gate n1(w0,s0);
    and_gate and1(w1,w0,x0);
    and_gate and2(w2,s0,x1);
    or_gate or1(y,w1,w2);

endmodule