module dff_async_low_pos_tb;

    wire q, q_bar;
    reg d, r, clk;

    initial 
        begin
            d =0;
            r =1;
            clk = 0;
        end

    always 
        #3 d = ~d;
    always
        #7 r = ~r;
    always
        #11 clk = ~clk;

    dff_async_low_positive df(q,q_bar,d,r,clk);

endmodule
