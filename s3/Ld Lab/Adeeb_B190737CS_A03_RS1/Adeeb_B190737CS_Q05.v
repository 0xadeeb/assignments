module RAM64(e,din,clk,adr,w,r,dout) ;

    output [15:0] dout ;
    input [15:0] din ;
    input clk,w,r,e ;
    input [5:0] adr ;
    wire cs1,cs2,cs0,cs3,cs4,cs5,cs6,cs7;
    wire [15:0] y1,y2,y3,y4,y5,y6,y7,y0 ;

    demux_1x8 dmux1(cs1,cs2,cs0,cs3,cs4,cs5,cs6,cs7,e,adr[5],adr[4],adr[3]);
    RAM8 R1(cs0,din,clk,adr[2:0],w,r,y0) ;
    RAM8 R2(cs1,din,clk,adr[2:0],w,r,y1) ;
    RAM8 R3(cs2,din,clk,adr[2:0],w,r,y2) ;
    RAM8 R4(cs3,din,clk,adr[2:0],w,r,y3) ;
    RAM8 R5(cs4,din,clk,adr[2:0],w,r,y4) ;
    RAM8 R6(cs5,din,clk,adr[2:0],w,r,y5) ;
    RAM8 R7(cs6,din,clk,adr[2:0],w,r,y6) ;
    RAM8 R8(cs7,din,clk,adr[2:0],w,r,y7) ;

    mux_16_8x1 Mx(dout,y0,y1,y2,y3,y4,y5,y6,y7,adr[5],adr[4],adr[3]);

endmodule