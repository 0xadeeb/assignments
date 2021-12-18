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

module q2(op,x,y,clk);

    input [15:0] x,y;
    output reg[31:0]op;
    input clk;
    reg [2:0] adr;
    wire [31:0] dout,out,sum,diff;
    reg [31:0] din,a,b;

    assign sum = x+y;
    assign diff = x-y;

    RAM r(dout,din,1'b1,clk,adr,1'b1,1'b1);

    always @(sum)
    begin
        din = sum ; adr = 3'b000 ; #3 a = dout ; #3 ; 
    end

    always @(diff)  
    begin
        din = diff ; adr = 3'b001 ; #3 b = dout ; #3 ;
    end

    always @(x or y)
    begin
        din = out; adr = 3'b010;  op = out; #3;
    end

    multiplier m(out,sum[15:0],diff[15:0],clk);


endmodule