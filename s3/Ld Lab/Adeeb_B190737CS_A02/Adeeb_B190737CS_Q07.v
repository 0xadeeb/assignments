module sixteenbit_negator(b,a);

    input[15:0] a;
    output[15:0] b;
    not_gate_16 na(b,a);

endmodule
