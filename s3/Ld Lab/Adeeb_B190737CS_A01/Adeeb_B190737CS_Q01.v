module not_gate(b,a); 
    input a;
    output b;
    nand nand_1(b,a,a);
endmodule