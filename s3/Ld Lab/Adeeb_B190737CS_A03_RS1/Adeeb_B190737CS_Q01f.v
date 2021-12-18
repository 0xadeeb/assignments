module dff_sync_fall(d, clk, r, q, q_bar);

    input d, clk, r;
    output q, q_bar;

    wire clk_not;

    not_gate na1(clk_not, clk);

    dff_sync_pos df(d,clk,r,q,q_bar);
endmodule