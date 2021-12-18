module full_tb();
    reg clk;
    reg[2:0] in;
    wire s,c;

    initial 
    begin
        clk =0;
        in =0;    
    end
    
    always #5 clk = ~clk;

    always @(posedge clk)
        in = in+1;
        

    full_adder fa(s,c,in[2],in[1],in[0]);
 
    
endmodule
