module alu(out,zr,ng,zx,nx,zy,ny,f,no,x,y);

    output [15:0] out;
    input [15:0] x,y;
    output zr,ng;
    input zx,nx,zy,ny,f,no;
    wire c,first_8,second_8;
    wire [15:0] zx_w,zy_w,ny_w1,nx_w1,nx_w2,ny_w2,f_w1,f_w2,x_final,y_final,f_final,f_bar;
    
    and_gate_16 and1(zx_w,x,16'b0);        
    and_gate_16 and2(zy_w,y,16'b0);        
    sixteenbit_negator n1(nx_w1,x);
    sixteenbit_negator n2(nx_w2,zx_w);
    sixteenbit_negator n3(ny_w1,y);
    sixteenbit_negator n4(ny_w2,zy_w);
    
    mux_16_4x1 mux1(x_final,x,zx_w,nx_w1,nx_w2,nx,zx);
    mux_16_4x1 mux2(y_final,y,zy_w,ny_w1,ny_w2,ny,zy);
    
    and_gate_16 and8(f_w1,x_final,y_final);
    sixteenbit_adder ad18(f_w2,c,x_final,y_final,1'b0);

    mux_16_2x1 mux3(f_final,f_w1,f_w2,f);
   
    sixteenbit_negator n8(f_bar,f_final);
    
    mux_16_2x1 mux6(out,f_final,f_bar,no);
    
    or_gate or3(ng,c,out[15]);

    or_8_inp or1(first_8,out[0],out[1],out[2],out[3],out[4],out[5],out[6],out[7]);
    or_8_inp or2(second_8,out[8],out[9],out[10],out[11],out[12],out[13],out[14],out[15]);
    nor_gate nor1(zr,first_8,second_8);


    
endmodule
