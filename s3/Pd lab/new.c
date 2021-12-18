#include<stdio.h>
#include<stdlib.h>
int n;
int sum;
char colors[7]="abcdef";
char *col_v;
int *ver;

int max_deg(int **g)
{
 
	int V;
	 for(int i=0;i<n;i++)
	 {
		  sum=0;
		  for(int j=0;j<n;j++){
		      sum+=g[i][j];
		       }
		      if(sum>0 && sum<=5)
			    { V=i; 
			       break;}

	 }
	 //printf("max_deg\n");
	 ver[V]=0;
	return V;

}
   

int no_adjacency(int **g,int pro_ver,char c)
{
 for(int i=0;i<n;i++)
{
 if(  g[pro_ver][i]==1 && c==col_v[i] )
 return 0;
}
return 1;
}
   


void color(int **g,int pro_ver)
{
 
 for(int i=0;i<6;i++)
{
  if((no_adjacency(g,pro_ver,colors[i]))==1)
    {col_v[pro_ver]=colors[i];
     break;}
}
printf("%s\n","ok");
}



void graph_color(int **g,int bal)
{
 //int ver=pro_v;
 //int rem_v=bal;

	int remove_ver;
	 if(bal==1)
	 {
	      for(int i=0;i<n;i++)
		 {
		   if(ver[i]==1)
		        { remove_ver=i; break;}
		  }

		 col_v[remove_ver]='a';
	  
	 }
	
	 else
	{
	 
	 	 
		 int flag=0;
		 int **v=(int**)malloc(n*sizeof(int*));
		for(int i=0;i<n;i++)
		 	v[i]=(int*)malloc(n*sizeof(int));
		 
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
			    v[i][j]=g[i][j];
		 
			}
		 }
		 //printf("graph\n");
		 remove_ver=max_deg(g);
		
		
			  for(int j=0;j<n;j++)
			   {
			   	
				 v[remove_ver][j]=0;
				 v[j][remove_ver]=0;
					     
			    }
			//printf("for loop\n");
			
		printf("%d\n",bal);
		bal--;
		printf("%d\n",bal);
		graph_color(v,bal);
		printf("%d\n",bal);
		color(g,remove_ver);

	}
}



void main()
{
	 int m,i,j,k;
	 scanf("%d",&n);
	 scanf("%d",&m);
	 //int g[n][n];
	 int **g;
	 g=(int**)malloc(n*sizeof(int*));
	 for(int i=0;i<n;i++)
	 	g[i]=(int*)malloc(n*sizeof(int));
	 for(int k=0;k<m;k++)
	 {
		  scanf("%d %d",&i,&j);
		  g[i][j]=1;
		  g[j][i]=1;
		 //g[i][i]=1;
		  //g[j][j]=1;
	}

	for(int i=0;i<n;i++)
	{
		 for(int j=0;j<n;j++)
		 {
			   if(g[i][j]!=1)
			   g[i][j]=0; 
			   printf("%d ",g[i][j]);
			
		 }
		printf("\n");
	}
	
	for(int i=0;i<n;i++)
		g[i][i]=1;
	
	col_v=(char*)malloc(n*sizeof(char));
	ver=(int*)malloc(n*sizeof(int));

	for(i=0;i<n;i++)
		ver[i]=1;

	graph_color(g,n);


	for(i=0;i<n;i++)
		printf("\n%c",col_v[i]);
	printf("\n");


}


