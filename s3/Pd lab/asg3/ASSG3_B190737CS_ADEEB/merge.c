#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
int count=0;
void merge(int *arr, int low, int mid, int high)
{
	int n1 = mid-low+1, n2 = high-mid, *l, *r ;
	l= (int*)calloc((n1+1),sizeof(int));
	r= (int*)calloc((n2+1),sizeof(int));
	for(int i=0; i<n1; i++)
		*(l+i)= *(arr+low+i);
	for(int j=0; j<n2; j++)
		*(r+j) = *(arr+mid+1+j);
	*(l+n1)=INT_MAX;
	*(r+n2)=INT_MAX;
	int i=0, j=0, k=low;
	while(k<=high)
	{
		if(*(l+i)<=*(r+j))
			*(arr+ k++) = *(l+ i++);
		
		else
		{
			if(i!=n1)
			{	count+= (mid-i+1);
				for(int k=i; k<=mid; k++)
					printf("(%d,%d) ",l[k],r[j]);
			}
			*(arr+ k++) = *(r+ j++);
		}
	}
	
	free(l);free(r);
	
}	

void merge_sort(int* a,int low,int high)
{
	if(low<high)
	{
		int mid= (high+low)/2;
		merge_sort(a,low,mid);
		merge_sort(a,mid+1,high);
		merge(a,low,mid,high);
	}
	
}
		
void print_array(int *arr, int n)
{
	printf("\n");
	for(int i=0; i<n; i++)
		printf("%d ", *(arr+i));
}

void main()
{
	int *ar, n;
	scanf("%d",&n);
	ar = (int*)malloc(n*sizeof(int));
	for(int i=0; i<n; i++)
		scanf("%d", ar+i);
	merge_sort(ar, 0, n-1);
	print_array(ar,n);
	printf("\n%d\n",count);
}
