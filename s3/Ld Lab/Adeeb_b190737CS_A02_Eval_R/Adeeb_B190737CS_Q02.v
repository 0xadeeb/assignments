module circuitII_dash(out_dash,zr_dash,ng_dash,x,y,zx,nx,zy,ny,f,f1,no,y_dash,zx_dash,nx_dash,zy_dash,ny_dash,f_dash,f1_dash,no_dash);

    output [15:0] out_dash;
    output zr_dash,ng_dash;
    input [15:0] x,y;
    input zx,nx,zy,ny,f,f1,no;
    input [15:0] y_dash;
    input zx_dash,nx_dash,zy_dash,ny_dash,f_dash,f1_dash,no_dash;
    wire[15:0] out0, out1, w_and;
    wire s;

    and_gate an1(s,f1,f1_dash);
    circuitll clll(out0,zr,ng,x,y,zx,nx,zy,ny,f,f1,no);
    circuitll cll(out1,zr_dash,ng_dash,y_dash,x,zx_dash,nx_dash,zy_dash,ny_dash,f_dash,f1_dash,no_dash);

    and_gate_16 and2(w_and,out0,out1);

   mux_16_2x1 mux2(out,out0,out1,s);
   
endmodule