module q5_tb;
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
        #15 x = x+1;
        #15 y = y+1; 
    end
    
    q5 a(r, x, y, clk);

endmodule
