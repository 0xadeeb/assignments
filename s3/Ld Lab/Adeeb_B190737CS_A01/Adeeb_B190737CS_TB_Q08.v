module and16_tb;
    reg [0:15]a,b;
    wire [0:15]c;
    integer i,j;
    always
    begin
        for(i=0;i<=65535;i=i+1)
            for(j=0;j<=65535;j=j+1)
            begin
                #10 a=i; b=j;
            end
    end

    and_gate_16 and3(c,a,b);

endmodule