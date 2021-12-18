module demux_1x8_tb();
    reg clk;
    reg[3:0] in;
    wire y0,y1,y2,y3,y4,y5,y6,y7;

    initial 
    begin
        clk =0;
        in =0;    
    end
    
    always #5 clk = ~clk;

    always @(posedge clk)
        in = in+1;
        

    demux_1x8 demux1(y0,y1,y2,y3,y4,y5,y6,y7,in[3],in[2],in[1],in[0]);
 
    
endmodule
