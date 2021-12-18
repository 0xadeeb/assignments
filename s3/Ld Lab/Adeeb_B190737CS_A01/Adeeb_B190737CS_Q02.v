module and_gate(c,a,b);
    input a,b;
    output c;
    wire e;
    nand na1(e,a,b);
    nand na2(c,e,e);
endmodule 