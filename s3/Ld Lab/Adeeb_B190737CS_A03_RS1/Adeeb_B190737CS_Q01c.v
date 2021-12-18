module nand_3(op, a, b, c);

    input a,b,c;
    output op;

    wire w1, w2;

    and_gate an1(w1, a, b);
    and_gate an2(w2, w1, c);
    not_gate na(op, w2);

endmodule

module dff_with_reset(q, q_bar, d, r, c, clk);

    output q, q_bar;
    input d, r, c, clk;
    wire r_not,d_not,w1, w2;
    
    not_gate n1(r_not, r);
    not_gate n2(d_not,d);

    nand (w1, d, clk);
    nand (w2,d_not, clk);
    
    nand_3 na3(q, w1, c, q_bar);
    nand_3 na4(q_bar, w2, r, q);

endmodule

module dff_async_high_positive(q, q_bar, d, r, clk);

    output q, q_bar;
    input d, r, clk;
    wire q1, q1_bar, r_not, clk_not;
    not_gate n1(clk_not, clk);
    not_gate n2(r_not, r);

    dff_with_reset df(q1, q1_bar, d, r_not, 1'b1, clk_not);
    dff_with_reset df1(q, q_bar, q1, r_not, 1'b1, clk);

endmodule