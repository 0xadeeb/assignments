module multiplier(op,x,y,clk);

    output [31:0] op;
    input [15:0] x,y;
    input clk;
    integer i;
    reg [31:0] prd;
    reg [15:0]temp;
    
    always @ (x,y)
    begin
        temp = x;
        prd = 0;

        for(i = 0; i<16; i = i+1)
        begin
            if(y[i])
                prd = prd + (x << i);
        end 
        
    end
    
    assign op = prd;

endmodule



module q1(op,x,y,clk);

    input [15:0] x,y;
    output reg[31:0]op;
    input clk;
    reg [2:0] adr;
    wire [31:0] dout,out;
    reg [31:0] din,a,b;

   RAM r(dout,din,1'b1,clk,adr,1'b1,1'b1);

    always @(x)
    begin
        din = {{32-16{1'b0}}, x} ; adr = 3'b000 ; #3 a = dout ; #3 ; 
    end

    always @(y)  
    begin
        din = {{32-16{1'b0}}, y} ; adr = 3'b001 ; #3 b = dout ; #3 ;
    end

    always @(a or b)
    begin
        din = out; adr = 3'b010; #3 op = dout; #3;
    end
        

    multiplier m(out,a[15:0],b[15:0],clk);


endmodule