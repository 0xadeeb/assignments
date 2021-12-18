module circuitll_tb();
    
    reg[31:0] x;
    reg zx,nx,zy,ny,f,f1,no;
    wire[15:0] out;
    wire zr,ng;


    initial 
    begin
        zx=1;nx=0;zy=1;ny=0;f=1;no=0;
        x=0;  
        f1= 0;
    end
    
    always 
    begin
        #5 zx=1;nx=1;zy=0;ny=1;f=1;f1=0;no=0;
        #5 zx=0;nx=0;zy=0;ny=1;f=1;f1=0;no=1;
        #5 zx=0;nx=1;zy=0;ny=1;f=0;f1=0;no=1;
        #5 zx=0;nx=0;zy=1;ny=1;f=1;f1=0;no=0;
        #5 zx=0;nx=1;zy=0;ny=0;f=1;f1=0;no=1;
        #5 zx=0;nx=0;zy=0;ny=0;f=0;f1=1;no=0;
        #5 zx=0;nx=1;zy=1;ny=1;f=1;f1=0;no=1;
        #5 x=x+1;
        #5 zx=0;nx=1;zy=0;ny=0;f=1;f1=0;no=0;
        
        
    end
        
    circuitll cll(out,zr,ng,x[15:0],x[31:16],zx,nx,zy,ny,f,f1,no);
 
    
endmodule
