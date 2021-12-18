module sixteenbit_adder_tb;
    reg clk;
    reg[31:0] a;
    wire[15:0] s;
    wire c;

    initial 
    begin
        clk =1;
        a =0;    
    end
    
    
    always #5 clk = ~clk;

    always @(posedge clk)
        a = a+1;
    
        
    sixteenbit_adder fa(s,c,a[15:0],a[31:16],1'b0);
 
    
endmodule
