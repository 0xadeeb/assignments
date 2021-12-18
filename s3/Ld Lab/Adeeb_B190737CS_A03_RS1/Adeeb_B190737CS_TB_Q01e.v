module dff_falling_tb;
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
        
    dff_falling df(q,q_bar,d,clk);

endmodule
