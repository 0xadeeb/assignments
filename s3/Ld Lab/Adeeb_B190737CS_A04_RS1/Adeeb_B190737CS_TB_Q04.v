module q4_tb;
    wire[15:0] q;
    reg [15:0] x,y;
    reg clk;

    initial 
    begin
        x = 2048;
        y = 1;
        clk = 0;
    end

    always
     #1 clk = ~clk;
     
    always
    begin
        #15 x = x+1;
        #15 y = y+3; 
    end
    
    q4 a(q, x, y, clk);

endmodule
