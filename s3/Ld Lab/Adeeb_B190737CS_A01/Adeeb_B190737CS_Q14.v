module mux_16_2x1(y,i0,i1,s0);

    output[15:0] y;
    input[15:0] i0,i1;
    input s0;
    
    mux_2x1 mux1[15:0](y,i0,i1,s0);
    
endmodule