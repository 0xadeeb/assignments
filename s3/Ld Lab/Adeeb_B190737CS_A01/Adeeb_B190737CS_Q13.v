module demux_1x2(y0,y1,x,s0);

    output y0,y1;
    input x,s0;
    wire s0_not;

    not_gate n1(s0_not,s0);
    and_gate and1(y0,s0_not,x);
    and_gate and2(y1,s0,x);

endmodule