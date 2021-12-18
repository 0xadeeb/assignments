module mux_2x1_16_tb;

    wire[15:0] op;
    reg[15:0] in[0:1];
    reg s;    
    integer i,j,k;
    
    initial
        s=1'b0;
        
    always
    begin
        for(k=0;k<2;k=k+1)
        begin
            for(j=0;j<=65535;j=j+1)
                for(i=0;i<65536;i=i+1)
                begin
                    #2 in[1]=j; in[0]=i;
                end
                s = ~s;
        end
        
    end
    
    mux_16_2x1 mux1(op,in[0],in[1],s);

endmodule