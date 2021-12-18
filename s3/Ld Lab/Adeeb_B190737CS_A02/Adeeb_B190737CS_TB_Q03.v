module fourbit_incrementer_tb();
    reg clk;
    reg[3:0] a;
    wire[3:0] s;
    wire c;

    initial 
    begin
        clk =1;
        a =0;    
    end
    
    
    always #5 clk = ~clk;

    always @(posedge clk)
    begin
        a = a+1;
    end
        
    fourbit_incrementer fa(s,c,a);
 
    
endmodule
