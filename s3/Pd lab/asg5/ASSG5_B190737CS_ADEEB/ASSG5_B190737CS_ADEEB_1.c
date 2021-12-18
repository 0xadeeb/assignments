#include<stdio.h>
#include<stdlib.h>

int cmp;

typedef struct heap
{
	int *arr, n;
}heap;

void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(heap *h,int i)
{
	int l, r, largest;
	largest = i;
	l= 2*i+1;
	r= 2*i+2;
	
	if(l<h->n&&++cmp&&h->arr[largest]<h->arr[l])
		largest=l;
	if(r<h->n&&++cmp&&h->arr[largest]<h->arr[r])
		largest=r;
	if(largest!=i)
	{	
		swap(h->arr+largest,h->arr+i);
		heapify(h,largest);
	}

}		
	
void heap_sort(heap *h)
{
	int temp = h->n;
	for(int i=h->n-1; i>0; i--)
	{
		swap(h->arr,h->arr+i);
		h->n=i;
		heapify(h,0);
	}
	h->n=temp;
}

void build_heap(heap *h)
{
	for(int i=h->n/2-1; i>=0; i--)
		heapify(h,i);

}

void main()
{
	heap *h;
	h = (heap*)malloc(sizeof(heap));
	scanf("%d",&h->n);
	h->arr = (int*)malloc(h->n*sizeof(int));
	
	for(int i=0; i<h->n; i++)
		scanf("%d",h->arr+i);
	
	build_heap(h);
	heap_sort(h);
	
	for(int i=0; i<h->n; i++)
		printf("%d ",h->arr[i]);
		
	printf("\n%d\n",cmp);
	free(h->arr);
	free(h);

}
