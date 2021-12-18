module xnor_tb;
    reg a,b;
    wire c;

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

    xnor_gate xn1(c,b,a);

endmodule 