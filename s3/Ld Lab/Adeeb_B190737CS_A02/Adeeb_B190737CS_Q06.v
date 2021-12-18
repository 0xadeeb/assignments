module sixteenbit_incrementer(s,c_out,a);

    input [15:0] a;
    output [15:0] s;
    output c_out;

    sixteenbit_adder fa1(s,c_out,a,16'b0000_0000_0000_0001,1'b0);

endmodule
