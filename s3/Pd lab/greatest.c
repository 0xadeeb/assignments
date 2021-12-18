#include<stdio.h>
void main()
{
	int a,b,res;
	printf("Enter 2 numbers\n");
	scanf("%d%d",&a,&b);
	a<=b?(res=b):(res=a);
	printf("The greatest is: %d\n", res);
}
