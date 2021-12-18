module fourbit_adder_tb();
    reg clk;
    reg[3:0] a,b;
    wire[3:0] s;
    wire c;

    initial 
    begin
        clk =1;
        a =0;
        b =0;    
    end
    
    
    always #5 clk = ~clk;

    always @(posedge clk)
    begin
        a = a+1;
        #5 b= b+1;
    end
        
        

    fourbit_adder fa(s,c,a,b,1'b0);
 
    
endmodule
