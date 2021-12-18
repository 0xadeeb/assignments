module q2_tb;

    wire[31:0] op;
    reg [15:0] x,y;
    reg clk;

    initial 
    begin
        x = 150;
        y = 0;
        clk = 0;
    end

    always
    begin
        x = x+1; #19;
        y = y+1; #19;
        clk = ~clk; #19; 
    end
    
    q2 a(op, x, y, clk);

endmodule
