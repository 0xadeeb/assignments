module sixteenbit_adder(s,c_out,a,b,c_in);

    input [15:0] a,b;
    input c_in;
    output [15:0] s;
    output c_out;
    wire w1,w2,w0;


    fourbit_adder fa1(s[3:0],w0,a[3:0],b[3:0],c_in);
    fourbit_adder fa2(s[7:4],w1,a[7:4],b[7:4],w0);
    fourbit_adder fa3(s[11:8],w2,a[11:8],b[11:8],w1);
    fourbit_adder fa4(s[15:12],c_out,a[15:12],b[15:12],w2);

endmodule
