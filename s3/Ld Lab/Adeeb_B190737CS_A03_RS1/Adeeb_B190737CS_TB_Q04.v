module RAM8_tb;

wire [15:0] dout ;
reg [15:0] din ;
reg e,clk,w,r ;
reg [2:0] adr ;

initial 
    begin 
        e = 1'b1 ;
        clk = 1'b1 ;
    end

always 
    begin 
        clk = ~clk ; #3 ;
    end

always 
    begin
        din = 100 ; adr = 0 ; w = 1'b1 ; r = 1'b0 ; #10 ;
        din = 200 ; adr = 1 ; w = 1'b1 ; r = 1'b0 ; #10 ;
        din = 300 ; adr = 2 ; w = 1'b1 ; r = 1'b0 ; #10 ;
        din = 400 ; adr = 3 ; w = 1'b1 ; r = 1'b0 ; #10 ;
        din = 500 ; adr = 4 ; w = 1'b1 ; r = 1'b0 ; #10 ;
        din = 600 ; adr = 5 ; w = 1'b1 ; r = 1'b0 ; #10 ;
        din = 700 ; adr = 6 ; w = 1'b1 ; r = 1'b0 ; #10 ;
        din = 800 ; adr = 7 ; w = 1'b1 ; r = 1'b0 ; #10 ;

        din = 0 ; adr = 0 ; w = 1'b0 ; r = 1'b1 ; #10 ;
        din = 0 ; adr = 1 ; w = 1'b0 ; r = 1'b1 ; #10 ;
        din = 0 ; adr = 2 ; w = 1'b0 ; r = 1'b1 ; #10 ;
        din = 0 ; adr = 3 ; w = 1'b0 ; r = 1'b1 ; #10 ;
        din = 0 ; adr = 4 ; w = 1'b0 ; r = 1'b1 ; #10 ;
        din = 0 ; adr = 5 ; w = 1'b0 ; r = 1'b1 ; #10 ;
        din = 0 ; adr = 6 ; w = 1'b0 ; r = 1'b1 ; #10 ;
        din = 0 ; adr = 7 ; w = 1'b0 ; r = 1'b1 ; #10 ;

    end


RAM8 r1(dout,din,e,clk,adr,w,r) ;

endmodule
