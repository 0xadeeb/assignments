module RAM8(dout,din,e,clk,adr,w,r) ;

    output [15:0] dout ;
    input [15:0] din ;
    input clk,w,r,e ;
    input [2:0] adr ;
    wire cs1,cs2,cs0,cs3,cs4,cs5,cs6,cs7;
    wire [15:0] y1,y2,y3,y4,y5,y6,y7,y0;

    demux_1x8 dmux1(cs0,cs1,cs2,cs3,cs4,cs5,cs6,cs7,e,adr[2],adr[1],adr[0]);

    register r1(y0,din,clk,w,r,cs0) ;
    register r2(y1,din,clk,w,r,cs1) ;
    register r3(y2,din,clk,w,r,cs2) ;
    register r4(y3,din,clk,w,r,cs3) ;
    register r5(y4,din,clk,w,r,cs4) ;
    register r6(y5,din,clk,w,r,cs5) ;
    register r7(y6,din,clk,w,r,cs6) ;
    register r8(y7,din,clk,w,r,cs7) ;

mux_16_8x1 M(dout,y0,y1,y2,y3,y4,y5,y6,y7,adr[2],adr[1],adr[0]) ;

endmodule