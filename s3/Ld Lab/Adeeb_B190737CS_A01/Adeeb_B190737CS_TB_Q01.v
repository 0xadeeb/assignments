module not_gate_tb();
    
    reg a;
    wire b;

    initial
    begin
        a=1'b0;
    end

    always
    begin
        #5 a=1'b1;
        #5 a=1'b0;
    end
    
    not_gate na1(b,a);
 
    
endmodule