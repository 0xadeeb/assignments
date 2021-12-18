#include<stdio.h>
#include<stdlib.h>
void main()
{
	int n , *f;
	printf("Enter the number:");
	scanf("%d",&n);
	f = (int*)malloc(n* sizeof(int));
	*f = 1;
	*(f+1) = 1;
	for(int i=2; i<n; i++)
		*(f+i)= *(f+i-1)+ *(f+i-2);
	for( int i=0; i<n; i++)
		printf("%d ",*(f+i));
	printf("\n");
}
