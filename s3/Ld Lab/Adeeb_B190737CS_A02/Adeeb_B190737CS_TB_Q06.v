module sixteenbit_incrementer_tb();
    reg clk;
    reg[15:0] a;
    wire[15:0] s;
    wire c;

    initial 
    begin
        clk =0;
        a =0;    
    end
    
    
    always #5 clk = ~clk;

    always @(negedge clk)
    begin
        a = a+1;
    end
        
    sixteenbit_incrementer fa(s,c,a);
 
    
endmodule
