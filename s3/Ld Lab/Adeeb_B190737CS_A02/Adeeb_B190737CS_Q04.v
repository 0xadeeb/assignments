module fourbit_adder(s,c_out,a,b,c_in);

    input [3:0] a,b;
    input c_in;
    output [3:0] s;
    output c_out;
    wire w1,w2,w0;


    full_adder fa1(s[0],w0,a[0],b[0],c_in);
    full_adder fa2(s[1],w1,a[1],b[1],w0);
    full_adder fa3(s[2],w2,a[2],b[2],w1);
    full_adder fa4(s[3],c_out,a[3],b[3],w2);

endmodule
