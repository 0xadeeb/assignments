module binary_cell_tb;

    wire d_out;
    reg [5:0]x;

    initial
        begin
            x = 0;
        end
    always
        #5 x = x+3;

    binary_cell bc(d_out, x[0],x[1],x[2],x[3],x[4]);

endmodule
