module xor_gate(c,a,b);
    input a,b;
    output c;

    wire w1,w2,w3,w4;

    nand na1(w1,a,a);
    nand na2(w2,b,b);
    nand na3(w3,w1,b);
    nand na4(w4,w2,a);
    nand na5(c,w4,w3);

endmodule