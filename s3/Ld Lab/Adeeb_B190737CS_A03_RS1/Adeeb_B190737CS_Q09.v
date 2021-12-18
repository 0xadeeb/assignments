module PC(dout,re,inc,load,din,clk,cs,w,r) ;

    input re,inc,load,clk,cs,w,r ;
    input [15:0] din ;
    output [15:0] dout ;
    wire [15:0] d,w1,w2,w3,x ;
    wire c;

    mux_16_2x1 mux1(d,dout,din,load) ;
    sixteenbit_incrementer in1(w1,c,d) ;
    mux_16_2x1 mux2(w3,d,w1,inc) ;
    mux_16_2x1 mux3(x,w3,16'b0,re);
    register r1(dout,x,clk,w,r,cs) ;

endmodule