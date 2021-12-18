module mux_2x1_tb();
    reg clk;
    reg [2:0]in;
    wire y;

    initial 
    begin
        clk =0;
        in =0;    
    end
    
    always #5 clk = ~clk;

    always @(posedge clk)
        in=in+1;
    
    mux_2x1 mux1(y,in[2],in[1],in[0]);
 
    
endmodule