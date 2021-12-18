module demux_1x4_tb();
    reg clk;
    reg[2:0] in;
    wire y0,y1,y2,y3;

    initial 
    begin
        clk =0;
        in =0;   
    end
    
    always #5 clk = ~clk;

    always @(posedge clk)
        in = in+1;
        

    demux_1x4 demux4(y0,y1,y2,y3,in[2],in[1],in[0]);
 
    
endmodule
