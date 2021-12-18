module or_8_inp(op,in0,in1,in2,in3,in4,in5,in6,in7);
    input in0,in1,in2,in3,in4,in5,in6,in7;
    output op;
    wire w0,w2,w1,w3,w4,w5;
    or_gate or0(w0,in1,in0);
    or_gate or1(w1,w0,in2);
    or_gate or2(w2,w1,in3);
    or_gate or3(w3,w2,in4);
    or_gate or4(w4,w3,in5);
    or_gate or5(w5,w4,in6);
    or_gate or6(op,w5,in7);
endmodule
    
    