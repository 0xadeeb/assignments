module not_gate_16(b,a); 
    input [15:0]a;
    output [15:0]b;
    not_gate not1[15:0] (b,a);
endmodule