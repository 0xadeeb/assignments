module RAM512(e,din,clk,adr,w,r,dout) ;

    output [15:0] dout ;
    input [15:0] din ;
    input clk,w,r,e ;
    input [8:0] adr ;
    wire cs1,cs2,cs0,cs3,cs4,cs5,cs6,cs7;
    wire [15:0] y1,y2,y3,y4,y5,y6,y7,y0 ;

    demux_1x8 dmux1(cs1,cs2,cs0,cs3,cs4,cs5,cs6,cs7,e,adr[8],adr[7],adr[6]);
    RAM64 R1(cs0,din,clk,adr[5:0],w,r,y0) ;
    RAM64 R2(cs1,din,clk,adr[5:0],w,r,y1) ;
    RAM64 R3(cs2,din,clk,adr[5:0],w,r,y2) ;
    RAM64 R4(cs3,din,clk,adr[5:0],w,r,y3) ;
    RAM64 R5(cs4,din,clk,adr[5:0],w,r,y4) ;
    RAM64 R6(cs5,din,clk,adr[5:0],w,r,y5) ;
    RAM64 R7(cs6,din,clk,adr[5:0],w,r,y6) ;
    RAM64 R8(cs7,din,clk,adr[5:0],w,r,y7) ;

    mux_16_8x1 Mx(dout,y0,y1,y2,y3,y4,y5,y6,y7,adr[8],adr[7],adr[6]);

endmodule