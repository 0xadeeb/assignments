module or_gate_16(c,a,b);
    input[15:0] a,b;
    output[15:0] c;
    
    or_gate or2[15:0] (c,a,b);

endmodule