module q1_tb;

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
        clk = ~clk;

    always
    begin
        x = x+1; #30;
        y = y+12; #30;
    end
    
    q1 a(op, x, y, clk);

endmodule
