module dff(d,clk,q,q_bar);
    input d, clk;
    output q, q_bar;
    wire d_bar, w1, w2;

    nand n1(d_bar,d);
    nand n2(w1,d,clk);
    nand n3(w2,d_bar,clk);
    nand n4(q, w1, q_bar);
    nand n5(q_bar, w2, q);

endmodule

module pos_dff(d,clk,q,q_bar);

    input d, clk;
    output q, q_bar;

    wire clk_bar, q1, q1_bar;

    nand n1(clk_bar,clk);

    dff df1(d, clk_bar, q1, q1_bar);

    dff df2(q1, clk, q, q_bar);
    
endmodule


module dff_falling(q,q_bar,d,clk);

    input d, clk;
    output q , q_bar;

    wire w;

    not_gate va(w , clk);

    pos_dff df(d, w, q, q_bar);

endmodule