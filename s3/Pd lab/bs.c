#include<stdio.h>
#include<stdlib.h>

void bubble_sort(int count, int* arr)
{
	for(int i=0; i<count; i++)
		for(int j=0; j<count-i-1; j++)
		{
			if(*(arr+j)>*(arr+j+1))
			{
				int temp = *(arr+j+1);
				*(arr+j+1) = *(arr+j);
				*(arr+j) = temp;
			}
		}		
	

}
void main()
{
	int *a, n, error;
	//printf("Enter the number of elements in the array:");
	error=scanf("%d",&n);
	if(!error)
		printf("Error not a number");
	else
	{	
		a = (int*)malloc( n* sizeof(int));
		//printf("Elements:\n");
		for(int i=0; i<n; i++)
			error = scanf("%d", a+i)&&error;
		if(!error)
			printf("Error not a number");
		else
		{
			bubble_sort(n, a);
			//printf("Sorted array is:");
			for(int i=0; i<n; i++)
				printf("%d ",*(a+i));
		}
	}
	//printf("\n");
}
