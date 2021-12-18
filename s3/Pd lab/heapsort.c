#include<stdio.h>
#include<stdlib.h>

int cmp;

void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(int *arr,int i,int n)
{
	int l, r, largest;
	largest = i;
	l= 2*i+1;
	r= 2*i+2;
	
	if(l<n&&++cmp&&arr[largest]<arr[l])
		largest=l;
	if(r<n&&++cmp&&arr[largest]<arr[r])
		largest=r;
	if(largest!=i)
	{	
		swap(arr+largest,arr+i);
		heapify(arr,largest,n);
	}

}		
	
void heap_sort(int *arr,int n)
{
	for(int i=n-1; i>0; i--)
	{
		swap(arr,arr+i);
		heapify(arr,0,i);
	}
}

void build_heap(int *arr,int n)
{
	for(int i=n/2-1; i>=0; i--)
		heapify(arr,i,n);

}

void main()
{
	int n, *arr;
	scanf("%d",&n);
	arr = malloc(n*sizeof(int));
	for(int i=0; i<n; i++)
		scanf("%d",arr+i);
	
	build_heap(arr,n);
	heap_sort(arr,n);
	
	for(int i=0; i<n; i++)
		printf("%d ",arr[i]);
	printf("\n%d\n",cmp);

}
