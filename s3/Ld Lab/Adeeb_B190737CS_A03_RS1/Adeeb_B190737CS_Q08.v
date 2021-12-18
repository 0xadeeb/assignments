module RAM16K(e,din,clk,adr,w,r,dout) ;

    output [15:0] dout ;
    input [15:0] din ;
    input clk,w,r,e ;
    input [13:0] adr ;
    wire cs1,cs2,cs0,cs3;
    wire [15:0] y1,y2,y3,y4,y5,y6,y7,y0 ;

    demux_1x4 dmux1(cs1,cs2,cs0,cs3,e,adr[13],adr[12]);
    RAM4K R1(cs0,din,clk,adr[11:0],w,r,y0) ;
    RAM4K R2(cs1,din,clk,adr[11:0],w,r,y1) ;
    RAM4K R3(cs2,din,clk,adr[11:0],w,r,y2) ;
    RAM4K R4(cs3,din,clk,adr[11:0],w,r,y3) ;

    mux_16_4x1 Mx(dout,y0,y1,y2,y3,adr[13],adr[12]);

endmodule

