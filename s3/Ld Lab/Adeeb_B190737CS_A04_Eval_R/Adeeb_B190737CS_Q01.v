module circuitIV_III(S,P,Q,R,operation);

    output reg [23:0] S;
    input [23:0] P,Q,R;
    input operation;
    reg [11:0] adr; 
    reg [23:0] op1_a, op2_a, op_a, op1_b, op2_b, op_b, op, din, dout,a,b;
    wire [23:0] q1, q2,q3;
    reg clk,r,w;

    always
     #1 clk = ~clk;

    multiplier m1(op1_a, P,Q);
    dividor d1(q1, op2_a, Q, R);

    always@ (Q,P,R)
    begin
        op1_b = P+Q;
        op2_b = R-Q;
    end

    always @(P)
    begin
        din =  P ; adr = 12'd55 ; r= 1'bx; #3 a = dout ; adr = 3'b000; #3;
    end

    always @(Q)
    begin
        din =  P ; adr = 12'd70 ; r= 1'bx; #3 a = dout ; adr = 3'b000; #3;
    end

    always @(R)  
    begin
        din = R ; adr = 12'd90 ; r= 1'bx; #3 b = dout ; adr = 3'b001;#3;
    end

    always @(op)
    begin
        din = op; adr = 3'b010; S=op; r = dout; adr = 12'd110; #3;
    end

    divider d2(q2,op_a,op1_a,op1_b);
    divider d5(q3,op_b,op1_b,op2_b);

    mux_24_2x1 mx(op,op_a, op_b, operation);

    RAM4K r43(1'b1,din, 1'b0, clk, adr, w, r, dout);

endmodule