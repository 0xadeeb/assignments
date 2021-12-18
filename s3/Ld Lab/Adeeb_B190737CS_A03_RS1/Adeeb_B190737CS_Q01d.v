module dff_async_low_positive(q, q_bar, d, r, clk);

    output q, q_bar;
    input d, r, clk;
    wire q1, q1_bar, r_not, clk_not;
    not_gate n1(clk_not, clk);
    not_gate n2(r_not, r);

    dff_with_reset df(q1, q1_bar, d, r_not, 1'b0, clk_not);
    dff_with_reset df1(q, q_bar, q1, r_not, 1'b0, clk);

endmodule
