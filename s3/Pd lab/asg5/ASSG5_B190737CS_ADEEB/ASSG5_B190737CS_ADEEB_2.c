#include<stdio.h>
#include<stdlib.h>

typedef struct heap
{
	int *arr,n;
} heap;

void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(heap *h,int i)
{
	int l, r,smallest,n=h->n;
	smallest = i;
	l= 2*i+1;
	r= 2*i+2;
	
	if(l<n&&h->arr[smallest]>h->arr[l])
		smallest=l;
	if(r<n&&h->arr[smallest]>h->arr[r])
		smallest=r;
	if(smallest!=i)
	{	
		swap(h->arr+smallest,h->arr+i);
		heapify(h,smallest);
	}

} 
	
void extract_min(heap* h)
{
	int n= h->n-1;
	if(n<0)
		printf("-1\n");
	else
	{
		printf("%d\n",h->arr[0]);
		h->arr[0]=h->arr[n];
		h->arr = (int*)realloc(h->arr,n*sizeof(int));
		heapify(h,0);
		h->n--;
	}
}

void increase(int* arr,int node)
{
	int parent = (node-1)/2;
	if(parent>=0&&arr[parent]>arr[node])
	{
		swap(arr+node,arr+parent);
		increase(arr,parent);
	}
}

void min_heap_insert(heap *h, int element)
{
	int n = h->n;
	h->n++;
	h->arr = (int*)realloc(h->arr,(n+1)*sizeof(int));
	h->arr[n]=element;
	increase(h->arr,n);
	
}

void decrease_key(heap *h, int i,int element)
{
	int n = h->n;
	if(element>h->arr[i])
	{
		h->arr[i]= element;
		heapify(h,i);
	}
	if(element<h->arr[i])
	{
		h->arr[i]= element;
		increase(h->arr,i);
	}
}

void heap_minimum(int *heap)
{
	printf("%d\n",*heap);
}

void main()
{
	heap *h=(heap*)malloc(sizeof(heap));
	int i,element;
	h->arr = (int*)malloc(sizeof(int));
	h->n = 0;
	char opt;
	
	scanf("%c",&opt);
	
	while(opt!='s')
	{
		switch(opt)
		{
			case 'i':
				scanf("%d",&element);
				min_heap_insert(h,element);
				break;
			case 'e':
				extract_min(h);
				break;
			case 'm':
				if(h->n<1)
					printf("-1\n");
				else
					heap_minimum(h->arr);
				break;
			case 'd':
				scanf("%d %d",&i,&element);
				decrease_key(h,i,element);
				break;
		}
		
		scanf("%c",&opt);
	}
	if(h->n>0)
		free(h->arr);
	free(h);
}
			
