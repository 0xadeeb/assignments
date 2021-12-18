module or_gate(c,a,b);

    input a,b;
    output c;
    wire w1,w2;
    nand na1(w1,a,a);
    nand na2(w2,b,b);
    nand na3(c,w2,w1);
    
endmodule