module half_adder(s,c,a,b);

    input a,b;
    output s,c;

    xor_gate xor1(s,a,b);
    and_gate and1(c,a,b);

endmodule
