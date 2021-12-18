module demux_1x4(y0,y1,y2,y3,x,s1,s0);

    input x,s0,s1;
    output y0,y1,y2,y3;
    wire w0,w1;

    demux_1x2 demux1(w0,w1,x,s1);
    demux_1x2 demux2(y0,y1,w0,s0);
    demux_1x2 demux3(y2,y3,w1,s0);

endmodule