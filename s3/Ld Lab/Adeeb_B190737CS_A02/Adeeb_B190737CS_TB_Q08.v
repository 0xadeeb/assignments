module alu_tb();
    
    reg[31:0] x;
    reg zx,nx,zy,ny,f,no;
    wire[15:0] out;
    wire zr,ng;

    initial 
    begin
        zx=1;nx=0;zy=1;ny=0;f=1;no=0;
        x=0;  
    end
    
    always 
    begin
        #5 zx=1;nx=1;zy=1;ny=1;f=1;no=1;
        #5 zx=1;nx=1;zy=1;ny=0;f=1;no=0;
        #5 zx=0;nx=0;zy=1;ny=1;f=0;no=0;
        #5 zx=1;nx=1;zy=0;ny=0;f=0;no=0;
        #5 zx=0;nx=0;zy=1;ny=1;f=0;no=1;
        #5 zx=1;nx=1;zy=0;ny=0;f=0;no=1;
        #5 zx=0;nx=0;zy=1;ny=1;f=1;no=1;
        #5 zx=1;nx=1;zy=0;ny=0;f=1;no=1;
        #5 zx=0;nx=1;zy=1;ny=1;f=1;no=1;
        #5 zx=1;nx=1;zy=0;ny=1;f=1;no=1;
        #5 zx=0;nx=0;zy=1;ny=1;f=1;no=0;
        #5 zx=1;nx=1;zy=0;ny=0;f=1;no=0;
        #5 zx=0;nx=0;zy=0;ny=0;f=1;no=0; 
        #5 zx=0;nx=1;zy=0;ny=0;f=1;no=1;
        #5 zx=0;nx=0;zy=0;ny=1;f=1;no=1;
        #5 zx=0;nx=0;zy=0;ny=0;f=0;no=0;
        #5 zx=0;nx=1;zy=0;ny=1;f=0;no=1;
        #5 x=x+1;
        #5 zx=0;nx=1;zy=0;ny=0;f=1;no=0;
        
    end
        
    alu a(out,zr,ng,zx,nx,zy,ny,f,no,x[15:0],x[31:16]);
 
    
endmodule
