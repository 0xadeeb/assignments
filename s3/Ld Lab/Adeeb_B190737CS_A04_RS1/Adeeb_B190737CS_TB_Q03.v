module q3_tb;
    wire[15:0] r;
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
        x = x+1; #15; 
        y = y+1; #15;
        
    end
    
    q3 a(r, x, y, clk);

endmodule
