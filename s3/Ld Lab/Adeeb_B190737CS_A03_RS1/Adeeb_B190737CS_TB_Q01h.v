module dff_async_low_neg_tb;

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

    dff_async_low_neg df(q,q_bar,d,r,clk);

endmodule
        
