module circuit_tb;

    wire[15:0] r;
    reg [15:0] x,y,z;
    reg option;

    initial 
    begin
        x = 2048;
        y = 1;
        z = 22;

        option = 0;
    end

    always
    begin
        #15 x = x+1;
        #15 y = y+1; 
        #15 z = z+1;
        #15 option = ~option;
    end
    
   circuitIV_III df(S,P,Q,R,operation);

endmodule 
    

