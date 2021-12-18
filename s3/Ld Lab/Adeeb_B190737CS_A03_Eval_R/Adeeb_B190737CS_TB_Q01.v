module RAM4K_tb ;

    wire [23:0] dout ;
    reg [23:0] din ;
    reg e, reset, clk,w,r ;
    reg [11:0] adr ;
    integer i ;

    initial 
        begin 
            e = 1'b1 ;
            clk = 1'b1 ;
            reset = 1'b0;
        end

    always 
        begin 
            clk = ~clk ; #3 ;
        end

    always 
        begin
            for(i=0;i<4097;i=i+1)
                begin
                    din = 7*i ; adr = i ; w =1'b1 ; r = 1'b0 ; #10 ;
                end
            din = din+3 ;
            for(i=0;i<4097;i=i+1)
                begin
                    adr = 4*i ; w =1'b0 ; r = 1'b1 ; #10 ;
                end

        end


RAM4K ra(e,din, reset, clk,adr,w,r,dout) ;

endmodule
