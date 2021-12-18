module mux_16_4x1(y,i0,i1,i2,i3,s1,s0);

    input[15:0] i0,i1,i2,i3;
    input s1,s0;
    output[15:0] y;
    wire[15:0] m0,m1;

    mux_16_2x1 mux1(m0,i0,i1,s0);
    mux_16_2x1 mux2(m1,i2,i3,s0);
    mux_16_2x1 mux3(y,m0,m1,s1);
    
endmodule

