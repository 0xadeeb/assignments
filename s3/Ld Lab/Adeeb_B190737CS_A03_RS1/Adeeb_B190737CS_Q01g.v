module dff_async_high_neg(q, q_bar, d, r, clk);

    output q, q_bar;
    input d, r, clk;

    wire clk_not;

    not_gate na(clk_not, clk);

    dff_async_high_positive as(q, q_bar, d, r, clk_not);
endmodule