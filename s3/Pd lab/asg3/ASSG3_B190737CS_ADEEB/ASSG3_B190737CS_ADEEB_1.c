#include<stdio.h>
#include<stdlib.h>

int insertion_sort(int *arr, int n)
{
	int temp,count=0;
	for(int i=1; i<n; i++)
	{
		temp= arr[i];
		int j=i-1;
		while(j>=0 && ++count && arr[j]>temp)
		{
			arr[j+1]= arr[j];
			j--;
		}
		arr[j+1]=temp;
	}
	return count;
}

void print_array(int* arr, int n)
{

	for(int i=0; i<n; i++)
		printf("%d ", *(arr+i));
}
	
void main()
{
	int *a, n, cmp;
	scanf("%d",&n);
	a = (int*)malloc(n*sizeof(int));
	for(int i=0; i<n; i++)
		scanf("%d", a+i);
	cmp = insertion_sort(a,n);
	print_array(a,n);
	printf("\n%d",cmp);
}
