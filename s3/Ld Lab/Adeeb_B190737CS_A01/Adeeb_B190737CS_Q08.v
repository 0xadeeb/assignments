module and_gate_16(c,a,b);
    input[15:0] a,b;
    output[15:0] c;
    
    and_gate and2[15:0] (c,a,b);

endmodule