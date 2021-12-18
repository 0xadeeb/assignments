#include<stdio.h>
#include<stdlib.h>

int ele,*arr,max;

int second(int a, int b)
{
	return b-a;
}
int first(int a, int b)
{
	return a-b;
}

int bs(int (*cmp_fn)(int,int), int low, int high)
{	
	if(ele==*(arr+max))
		return max;
	if(cmp_fn(*(arr+high),*(arr+low))<0)
		return -1;
	else
	{	
		int mid= (high+low)/2;
		if(ele==*(arr+mid))
			return mid;
		else
		{
			if(cmp_fn(*(arr+mid),ele)>0)
				return bs(cmp_fn,low,mid-1);
			if(cmp_fn(*(arr+mid),ele)<0)
				return bs(cmp_fn,mid+1,high);
		}
	}
}


void main()
{
	int n, pos1,pos2,pos,i;
	scanf("%d",&n);
	arr= (int*)malloc(n*sizeof(int));
	for(int i=0; i<n; i++)
		scanf("%d",arr+i);
	scanf("%d",&ele);
	for(max=1; max<n-1; max++)
		if(*(arr+max)>*(arr+max-1)&&*(arr+max)>*(arr+max+1))
			break;
	
	int low=0, high=n-1;
	pos1 = bs(first, low, max);
	pos2 = bs(second, max, high);
	pos1!=-1?(pos=pos1):(pos=pos2);
	printf("%d",pos);
}
