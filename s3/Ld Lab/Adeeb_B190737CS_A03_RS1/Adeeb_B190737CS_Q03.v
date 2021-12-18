module register(data_out, data_in, cs, w,r, clk);

    output [15:0]data_out;
    input [15:0]data_in;
    input cs, w,r, clk;

    binary_cell bc[15:0] (data_out, data_in , cs ,w,r, clk);
endmodule