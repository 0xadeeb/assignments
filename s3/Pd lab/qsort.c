#include<stdlib.h>
#include<stdio.h>

int cmp=0;

void swap(int *a, int *b)
{
	int temp = *a;
	*a= *b;
	*b=temp;
}
	

void partition(int* arr, int p, int* q, int r)
{
	int j=p;
	for(int i=p; i<r; i++)
		if(++cmp&&arr[i]<arr[r]&&i!=j++)
			swap(arr+j-1,arr+i);
			
	swap(arr+j,arr+r);
	*q = j;
}


void quick_sort(int* arr, int p, int r)
{
	int q;
	if(p<r)
	{
		partition(arr,p,&q,r);
		quick_sort(arr,p,q-1);
		quick_sort(arr,q+1,r);
	}
}

void print(int* a, int n)
{
	for(int i=0; i<n; i++)
		printf("%d ", *(a+i));
}

void main()
{
	int *a , n;
	scanf("%d",&n);
	a= (int*)malloc(n*sizeof(int));
	for(int i=0; i<n; i++)
		scanf("%d",a+i);
	quick_sort(a,0,n-1);
	print(a,n);
	printf("\n%d",cmp);

}
