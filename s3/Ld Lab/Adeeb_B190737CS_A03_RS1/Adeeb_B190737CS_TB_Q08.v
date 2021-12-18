module RAM16K_tb ;

    wire [15:0] dout ;
    reg [15:0] din ;
    reg e,clk,w,r ;
    reg [13:0] adr ;
    integer i ;

    initial 
        begin 
            e = 1'b1 ;
            clk = 1'b1 ;
            din = 7 ; adr = 5 ; w =1'b1 ; r = 1'b0 ; #10 ;
        end

    always 
        begin 
            clk = ~clk ; #3 ;
        end

    always 
        begin
            for(i=0;i<4097;i=i+1)
                begin
                    din = 7*i ; adr = i ; w =1'b0 ; r = 1'b1 ; #10 ;
                end
            din = din+3 ;
            for(i=0;i<4097;i=i+1)
                begin
                    adr = 4*i ; w =1'b1 ; r = 1'b1 ; #10 ;
                end

        end


RAM16K ra(e,din,clk,adr,w,r,dout) ;

endmodule
