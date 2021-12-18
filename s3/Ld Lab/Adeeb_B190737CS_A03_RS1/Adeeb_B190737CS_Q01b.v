module dff_sync_pos(d,clk,r,q,q_bar);

    input d,clk,r;
    output q, q_bar;

    wire r_bar, w;

    not_gate na(r_bar, r);

    and_gate and1(w, r_bar, d);

    dff_pos dff1(w, clk, q, q_bar);

endmodule