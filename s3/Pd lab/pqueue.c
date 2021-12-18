#include<stdio.h>
#include<stdlib.h>

void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(int *arr,int i,int n)
{
	int l, r,smallest;
	smallest = i;
	l= 2*i+1;
	r= 2*i+2;
	
	if(l<n&&arr[smallest]>arr[l])
		smallest=l;
	if(r<n&&arr[smallest]>arr[r])
		smallest=r;
	if(smallest!=i)
	{	
		swap(arr+smallest,arr+i);
		heapify(arr,smallest,n);
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
	
void extract_min(int* heap, int n)
{
	if(n<0)
		printf("-1\n");
	else
	{
		printf("%d\n",heap[0]);
		swap(heap,heap+n);
		heap = (int*)realloc(heap,n*sizeof(int));
		heapify(heap,0,n);
	}
}

void min_heap_insert(int *heap, int n, int element)
{
	
	heap = (int*)realloc(heap,(n+1)*sizeof(int));
	heap[n]=element;
	increase(heap,n);
	
}

void decrease_key(int *heap, int i, int n,int element)
{
	if(element>heap[i])
	{
		heap[i]= element;
		heapify(heap,i,n);
	}
	if(element<heap[i])
	{
		heap[i]= element;
		increase(heap,i);
	}
}

void heap_minimum(int *heap)
{
	printf("%d\n",*heap);
}

void main()
{
	int *heap=(int*)malloc(sizeof(int)), c=0,i,element;
	char opt;
	
	scanf("%c",&opt);
	
	while(opt!='s')
	{
		switch(opt)
		{
			case 'i':
				scanf("%d",&element);
				min_heap_insert(heap,c++,element);
				break;
			case 'e':
				extract_min(heap,--c);
				break;
			case 'm':
				if(c<0)
					printf("-1\n");
				else
					heap_minimum(heap);
				break;
			case 'd':
				scanf("%d %d",&i,&element);
				decrease_key(heap,i,c,element);
				break;
		}
		
		scanf("%c",&opt);
	}
	if(c>0)
		free(heap);
}
			
