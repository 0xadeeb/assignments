module halfadder_tb;
    reg a,b;
    wire s,c;

    initial
    begin
        a=1'b0; b=1'b0;
    end
    
    always
    begin
        #5 a=1'b0; b=1'b1;
        #5 a=1'b1; b=1'b0;
        #5 a=1'b1; b=1'b1;
        #5 a=1'b0; b=1'b0;
    end


    half_adder ha1(s,c,a,b);

endmodule
