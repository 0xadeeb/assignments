module RAM4K(e,din, reset, clk,adr,w,r,dout) ;

    output [23:0] dout ;
    input [23:0] din ;
    input reset, clk,w,r,e ;
    input [11:0] adr ;
    wire cs1,cs2,cs0,cs3,cs4,cs5,cs6,cs7;
    wire [23:0] y1,y2,y3,y4,y5,y6,y7,y0 ;

    demux_1x8 dmux1(cs1,cs2,cs0,cs3,cs4,cs5,cs6,cs7,e,adr[11],adr[10],adr[9]);
    RAM512 R1(cs0,din, reset, clk,adr[8:0],w,r,y0) ;
    RAM512 R2(cs1,din, reset, clk,adr[8:0],w,r,y1) ;
    RAM512 R3(cs2,din, reset, clk,adr[8:0],w,r,y2) ;
    RAM512 R4(cs3,din, reset, clk,adr[8:0],w,r,y3) ;
    RAM512 R5(cs4,din, reset, clk,adr[8:0],w,r,y4) ;
    RAM512 R6(cs5,din, reset, clk,adr[8:0],w,r,y5) ;
    RAM512 R7(cs6,din, reset, clk,adr[8:0],w,r,y6) ;
    RAM512 R8(cs7,din, reset, clk,adr[8:0],w,r,y7) ;

    mux_16_8x1 Mx(dout,y0,y1,y2,y3,y4,y5,y6,y7,adr[11],adr[10],adr[9]);

endmodule