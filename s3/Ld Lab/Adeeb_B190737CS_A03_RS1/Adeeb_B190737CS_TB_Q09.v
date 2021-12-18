module PC_tb ;

    reg re,inc,load,clk,cs,w,r ;
    reg [15:0] din ;
    wire [15:0] dout ;


    initial 
        begin 
            clk = 1'b0 ;
        end

    always 
        begin 
            clk = ~clk ; #1 ;
        end


    always 
        begin
            re = 1'b1 ; inc = 1'b0 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b0 ; din = 259;load = 1'b1 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b0 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b0 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b0 ; din = 0 ; load = 1'b1 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b0 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;
            re = 1'b1 ; inc = 1'b1 ; din = 0 ; load = 1'b0 ; cs = 1'b1 ; w = 1'b1 ; r = 1'b1 ; #5 ;

        end

        PC p1(dout,re,inc,load,din,clk,cs,w,r);

endmodule
