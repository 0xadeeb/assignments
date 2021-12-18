module fourbit_incrementer(s,c_out,a);

    input [3:0] a;
    output [3:0] s;
    output c_out;

    fourbit_adder fa1(s,c_out,a,4'b0001,1'b0);


endmodule
