#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void read(int* A, int* B, int n)
{
	for(int i=0; i<n; i++)
		scanf("%d %d",(B+i),A+i);	
}

int min_t(int *selection, int *condition, int* tmp, int n, int time, int loop)
{
	if(n==1)
		return *tmp;
	
	int j=0, min=INT_MAX;
	
	for(int i=0; i<n; i++)
		if(min>*(selection+*(tmp+i))&&*(condition+*(tmp+i))<=time)
			min=*(selection+*(tmp+i));
	for(int i=0; i<n; i++)
		if(*(selection+*(tmp+i))==min && *(condition+*(tmp+i))<=time)
			tmp[j++]=i;
				
	tmp = (int*)realloc(tmp , j*sizeof(int));
		
	if(j==1)
		return *tmp;
	
	
	j=0; min=INT_MAX;
	
	for(int i=0; i<n; i++)
		if(min> *(condition+*(tmp+i)))
			min= *(condition+*(tmp+i));
	for(int i=0; i<n; i++)
		if(*(condition+*(tmp+i))==min)
			tmp[j++]=i;
				
	return *tmp;
	
}


void run_processes(int* p,int* ini,int * res,int n,int t)
{
	int time=0, sum=1;
	while(sum!=0)
	
	{
		int *tmp= (int*)malloc(n*sizeof(int)),i,j=0;
		
		for(i=0; i<n; i++)
			if(p[i]=!-1)
				tmp[j++]=i;
		
		tmp = (int*)realloc(tmp , j*sizeof(int));		
			
		i = min_t(p,ini,tmp,j,time,2);
		
		if(p[i]>t)
		{
			time= time+t;
			p[i]-=t;
		}
		else
		{
			res[i]=time+p[i];
			p[i] =-1;
			time+=t;
		}
		sum=0;
			
		for(int i=0; i<n; i++)
			sum=sum+p[i]+1;
		
		free(tmp);
	}
	
	
	
}
void list_process(int *A,int n)
{
	for(int i=0; i<n; i++)
		printf("%d \n",*(A+i));
}

void main()
{
	int *ini, *p,*res, n, t;
	scanf("%d",&n);
	scanf("%d",&t);
	p = (int*)malloc(n*sizeof(int));
	ini = (int*)malloc(n*sizeof(int));
	res = (int*)malloc(n*sizeof(int));
	read(p,ini,n);
	run_processes(p,ini,res,n,t);
	list_process(res, n);
}
