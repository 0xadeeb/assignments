module mux_4x1_16_tb;

    wire[15:0] op;
    reg[15:0] in0,in1,in2,in3;
    reg s1,s0;
    integer i1,i0,i3,i2,j0,j1;
    
    initial
    begin
         s0 = 1'b0;
         s1 = 1'b0;
    end
       
    always
    begin
        for(j1=0;j1<2;j1=j1+1)
        begin
            for(j0=0;j0<2;j0=j0+1)
            begin
                for(i3=0;i3<=65535;i3=i3+1)
                    for(i2=0;i2<65536;i2=i2+1)
                        for(i1=0;i1<65536;i1=i1+1)
                            for(i0=0;i0<65536;i0=i0+1)
                            begin
                                #5 in0=i0; in1=i1; in2=i2; in3=i3;
                            end
                s0 = ~s0;
            end
           s1 = ~s1;
        end
    end
    
     mux_16_4x1 mux1(op,in0,in1,in2,in3,s1,s0);

endmodule