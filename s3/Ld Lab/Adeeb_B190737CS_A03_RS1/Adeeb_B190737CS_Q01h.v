module dff_async_high_neg(q, q_bar, d, r, clk);

    output q, q_bar;
    input d, r, clk;

    wire clk_not;

    not_gate na(clk_not, clk);

    dff_async_high_positive as(q, q_bar, d, r, clk_not);
endmodule

module dff_async_low_neg(q, q_bar, d, r, clk);

    output q, q_bar;
    input d, r, clk;

    wire r_not;

    not_gate na(r_not, r);
    dff_async_high_neg dff1(q, q_bar, d, r_not, clk);
endmodule