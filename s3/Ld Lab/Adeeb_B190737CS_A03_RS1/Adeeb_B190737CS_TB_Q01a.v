module dff_tb;
    wire q, q_bar;
    reg d,clk;

    initial
        begin
            clk = 0;
            d = 0;
        end

    always
        begin
            #5 d = ~d;
            
        end
    always
        #12 clk = ~clk;
        
    pos_dff df(d,clk,q,q_bar);

endmodule
