module negator16_tb;
    wire [15:0] b;
    reg [15:0] a;
    integer i;

    always    
    begin
        i=0;
        while(i<65536)
        begin
            a=i;
            #10 i=i+1;
        end
    end

    sixteenbit_negator ng1(b,a);
endmodule
