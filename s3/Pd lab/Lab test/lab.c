#include<stdio.h>
#include<stdlib.h>

void swap(float *a, float *b)
{
	float temp = *a;
	*a= *b;
	*b=temp;
}

void combine(float *l, float* r, int n1, int n2)
{
	int size = n2+1;
	for(int i=0; i<n1; i++)
		for(int j= 0; j<size; j++)
		{
			if(l[i]<r[j])
			{
				swap(l+i,r+j);
				j++;
				while(j<size)
				{
					swap(l+i,r+j);
					j++;
				}
				size++;
				continue;
			}
			if(j== size-1)
				r[j] = l[i];
		}
			
}

void main()
{
	int n1,n2;
	float *l,*r;
	scanf("%d",&n1);
	scanf("%d",&n2);
	l = (float*)malloc(n1*sizeof(float));
	r = (float*)malloc((n1+n2)*sizeof(float));
	for(int i=0; i<n1; i++)
		scanf("%f",l+i);
	for(int i=0; i<n2; i++)
		scanf("%f",r+i);
		
	combine(l,r,n1,n2);
	for(int i=0; i<(n2+n1); i++)
		printf("%.2f ",r[i]);
	printf("\n");	
}
	
	
