module demux_1x2_tb;

    reg s0,x;
    wire y0,y1;

    always 
    begin
    s0 = 0; x = 0;
    #10; s0=0;x=1;
    #10; s0=1;x=0;
    #10; s0=1;x=1;
    end

    demux_1x2 demux1(y0,y1,x,s0);

endmodule
