module dff_async_high_pos_tb;

    wire q, q_bar;
    reg d, r, clk;

    initial 
        begin
            d =0;
            r =0;
            clk = 0;
        end

    always 
        #3 d = ~d;
    always
        #7 r = ~r;
    always
        #11 clk = ~clk;

    dff_async_high_positive df(q,q_bar,d,r,clk);

endmodule
