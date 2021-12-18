module circuitll(out,zr,ng,x,y,zx,nx,zy,ny,f,f1,no);

    output [15:0] out;
    input [15:0] x,y;
    output zr,ng;
    input zx,nx,zy,ny,f,f1,no;
    wire c;
    wire [15:0] w1, w0;

    alu a1(w0,zr,ng,zx,nx,zy,ny,f,no,x,y );
    or_gate_16 or1(w1,x,16'b0000_1000_0000_0000);

    mux_16_2x1 mux1(out,w0,w1,f1);

endmodule