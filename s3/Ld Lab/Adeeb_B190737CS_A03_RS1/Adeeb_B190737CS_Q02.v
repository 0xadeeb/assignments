module binary_cell(data_out, data_in, cs, w,r, clk);

    output data_out;
    input data_in, cs, w,r, clk;

    wire q, q_bar, s1, s2, d, w,r_not;

    and_gate an1(s1, w, cs);
    and_gate an2(s2, r, cs);
    mux_2x1 mux1(d, q, data_in, s1);

    pos_dff df1(d,clk, q, q_bar);
    mux_2x1 mux2(data_out, 1'bx, q, s2);


endmodule