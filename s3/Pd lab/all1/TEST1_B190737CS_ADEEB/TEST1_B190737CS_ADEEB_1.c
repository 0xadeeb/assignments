#include<stdio.h>
#include<stdlib.h>

void read_and_store(int* A, int n)
{
	for(int i=0; i<n; i++)
		scanf("%d", A+i);
}

void run_processes(int* A,int* B,int n,int t)
{
	int time=0, sum=1, loop=0;
	while(sum!=0)
	{
		loop++;
		
		for( int i=0; i<n; i++)
		{
			if(A[i]==0&&loop!=1)
				continue;
			if(A[i]>t)
			{
				time= time+t;
				A[i]-=t;
			}
			else
			{
				int temp = t-A[i];
				time += A[i];
				B[i]= time;
				A[i] =0;
				time+=temp;
			}
		}
	sum-=1;
	for(int i=0; i<n; i++)
		sum+=A[i];
	}
		
}
void list_process(int *B,int n)
{
	for(int i=0; i<n; i++)
		printf("%d ", *(B+i));
}

void main()
{
	int *A, *B, n, t;
	scanf("%d",&n);
	A = (int*)malloc(n*sizeof(int));
	B = (int*)malloc(n*sizeof(int));
	read_and_store(A,n);
	scanf("%d",&t);
	run_processes(A, B, n, t);
	list_process(B, n);
}
