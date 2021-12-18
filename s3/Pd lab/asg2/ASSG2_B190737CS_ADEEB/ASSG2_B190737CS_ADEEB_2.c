#include<stdio.h>

long double fact(long double n)
{
	if(n<=1)
		return 1;
	else
		return n* fact(n-1);
}
		

void main()
{
	long double n, f;
	scanf("%Lf",&n);
	f = fact(n);
	printf("%.0Lf",f);
}	
