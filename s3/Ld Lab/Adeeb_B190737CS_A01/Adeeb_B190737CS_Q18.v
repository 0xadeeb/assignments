module demux_1x8(y0,y1,y2,y3,y4,y5,y6,y7,x,s2,s1,s0);

    input x,s0,s1,s2;
    output y0,y1,y2,y3,y4,y5,y6,y7;
    wire w0,w1,w2;

    demux_1x2 demux1(w0,w1,x,s2);
    demux_1x4 demux2(y0,y1,y2,y3,w0,s1,s0);
    demux_1x4 demux3(y4,y5,y6,y7,w1,s1,s0);

endmodule