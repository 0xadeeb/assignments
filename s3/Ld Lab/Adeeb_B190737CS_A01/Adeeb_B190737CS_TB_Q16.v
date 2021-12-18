module mux_8x1_16_tb;

    wire[15:0] op;
    reg[15:0] in0,in1,in2,in3,in4,in5,in6,in7;
    reg s2,s1,s0;
    
    integer i0,i1,i2,i3,i4,i5,i6,i7,j0,j1,j2;
    
    initial
    begin
         s0 = 1'b0;
         s1 = 1'b0;
         s2 = 1'b0;
    end
    
    always
    begin
        for(j2=0;j2<2;j2=j2+1)
        begin
            for(j1=0;j1<2;j1=j1+1)
            begin
                for(j0=0;j0<2;j0=j0+1)
                begin
                    for(i7=0;i7<=65535;i7=i7+1)
                        for(i6=0;i6<=65535;i6=i6+1)
                            for(i5=0;i5<=65535;i5=i5+1)
                                for(i4=0;i4<=65535;i4=i4+1)
                                    for(i3=0;i3<=65535;i3=i3+1)
                                        for(i2=0;i2<65536;i2=i2+1)
                                            for(i1=0;i1<65536;i1=i1+1)
                                                for(i0=0;i0<65536;i0=i0+1)
                                                begin
                                                    #5 in0=i0; in1=i1; in2=i2; in3=i3; in4=i4; in5=i5; in6=i6; in7=i7;
                                                end
                    s0 = ~s0;
                end
                s1 = ~s1;
            end
            s2= ~s2;
        end
    end
    
    mux_16_8x1 mux1(op,in0,in1,in2,in3,in4,in5,in6,in7,s2,s1,s0);
endmodule
