#include<stdio.h>
#include<stdlib.h>

int ele;
int binary_search(int *arr,int low,int high)
{
	if(low>high)
		return -1;
	else
	{	
		int mid=(high+low)/2;
		if(ele==*(arr+mid))
		{	
			int i;
			for(i=mid-1;*(arr+i)==*(arr+i+1)&&i>=0; i--);
			return i+1;
		}
			
				
		else
		{
			if(*(arr+mid)<ele)
				return binary_search(arr,mid+1,high);
			if(*(arr+mid)>ele)
				return binary_search(arr,low,mid-1);
		}
	}
}
void main()
{
	int *arr, n, pos, m, *res;
	scanf("%d %d",&n,&m);
	res = (int*)malloc(m*sizeof(int));
	arr = (int*)malloc(n*sizeof(int));
	for(int i=0; i<n; i++)
		scanf("%d ",arr+i);
	int j=0;
	while(j<m)
	{
		scanf("%d",&ele);
		int low=0, high=n-1;
		*(res+j) = binary_search(arr,low,high);
		j++;
	}
	for(int i=0; i<m; i++)
		printf("%d\n",*(res+i));
}
	

