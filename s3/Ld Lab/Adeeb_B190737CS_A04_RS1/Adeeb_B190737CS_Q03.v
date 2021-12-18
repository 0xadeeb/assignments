module divider(q,r,x,y,clk);
     
    output [15:0] q,r;
    input [15:0] x,y;

    input clk;
    integer i;
    reg [15:0] rem, qnt, temp_x;

    always @ (x,y)
    begin
        temp_x = x;
        rem = 16'b0;
        qnt = 16'b0;
        for(i =0 ; i< 16; i = i+1)
        begin
            {rem,temp_x} = {rem,temp_x} << 1;
            qnt = qnt << 1;
            if(rem>=y)
            begin
                rem = rem-y;
                qnt = qnt+1;
            end
        end
    end
    
    assign q = qnt;
    assign r = rem;

endmodule

module q3(r,x,y,clk);

    input [15:0]x,y;
    input clk;
    output reg[15:0] r;
    wire [15:0]q;
    reg [2:0] adr;
    wire [15:0] dout,out;
    reg [15:0] din,a,b;

    RAM8 r1(dout,din,1'b1,clk,adr,1'b1,1'b1);

    always @(x)
    begin
        din =  x ; adr = 3'b000 ;r =1'bx; #3 a = dout ; adr = 3'b000; #3; 
    end

    always @(out)
    begin
        din = out; adr = 3'b010; #3 r = dout; adr = 3'b010; #3;
    end

    always @(y)  
    begin
        din = y ; adr = 3'b001 ; r = 1'bx;#3 b = dout ; adr = 3'b001; #3;
    end

    always @(out)
    begin
        din = out; adr = 3'b010; #3 r = dout; adr = 3'b010; #3;
    end

    divider d(q,out,a,b,clk);
endmodule