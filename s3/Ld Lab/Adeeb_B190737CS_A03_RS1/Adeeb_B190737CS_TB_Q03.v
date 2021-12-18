module register_tb;

    wire [15:0]d_out;
    reg [3:0]x;
    reg [15:0]d_in;

    initial
        begin
            x = 0;
            d_in = 0;
        end
    always
        begin
            #5 x = x+3;
            #5 d_in = d_in+1;
        end

    register bc(d_out, d_in, x[0],x[1],x[2],x[3]);

endmodule
