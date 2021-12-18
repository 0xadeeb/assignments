module RAM512_tb ;

    wire [15:0] dout ;
    reg [15:0] din ;
    reg e,clk,w,r ;
    reg [8:0] adr ;
    integer i ;

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
            for(i=0;i<64;i=i+1)
                begin
                    din = i ; adr = i ; w =1'b1 ; r = 1'b0 ; #10 ;
                end
            din = din+3 ;
            for(i=0;i<64;i=i+1)
                begin
                    adr = i ; w =1'b0 ; r = 1'b1 ; #10 ;
                end

        end


RAM512 ra(e,din,clk,adr,w,r,dout) ;

endmodule
