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
		h->n--;
		heapify(h,0);
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

void change_key(heap *h, int k,int x)
{
	int i;
	for(i=0; i< h->n && h->arr[i] != k; i++);
		
	h->arr[i] = x;
	increase(h->arr,i);
	
}

void heap_minimum(int *heap)
{
	printf("%d\n",*heap);
}

void display_token(heap *h)
{
	heap *temp = (heap*)malloc(sizeof(heap)); 
	temp->arr = (int*)malloc(h->n*sizeof(int)); 
	temp->n= h->n;
	for(int i=0; i<=h->n; i++)
		temp->arr[i]= h->arr[i];
		
	for(int i=h->n-1; i>0; i--)
	{
		swap(temp->arr,temp->arr+i);
		temp->n=i;
		heapify(temp,0);
	}
	
	for(int i=h->n-1; i>=0; i--)
		printf("%d ",temp->arr[i]);
	printf("\n");
	free(temp->arr);free(temp);
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
			case 'c':
				scanf("%d %d",&i,&element);
				change_key(h,i,element);
				break;
			case 'd':
				display_token(h);
		}
		
		scanf("%c",&opt);
	}
	if(h->n>0)
		free(h->arr);
	free(h);
}
			
