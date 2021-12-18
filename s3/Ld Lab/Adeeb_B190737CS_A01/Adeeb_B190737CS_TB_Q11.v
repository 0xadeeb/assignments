module or_8_tb;

    wire op;
    reg[7:0] in; 
    reg clk;   

    initial
    begin
        in =0;
        clk=0;
    end

    always #5 clk= ~clk;

    always @(posedge clk)
        in=in+1;
    

    or_8_inp or7(op,in[0],in[1],in[2],in[3],in[4],in[5],in[6],in[7]);

endmodule