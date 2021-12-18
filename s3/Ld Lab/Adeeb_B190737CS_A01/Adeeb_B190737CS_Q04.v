module nor_gate (c,a,b);

    input a,b;
    output c;
    wire w;

    or_gate or1(w,a,b);
    not_gate not1(c,w);

endmodule