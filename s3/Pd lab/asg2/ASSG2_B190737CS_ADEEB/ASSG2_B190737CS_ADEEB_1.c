#include<stdio.h>
#include<stdlib.h>

int a,b,l;
int gcd(int i, int g)
{
	if(!l)
	{
		if(a==0&&b==0)
			return -1;
		else
			return a+b;
	}
	if(i>l)
		return g;
	else
		if(a%i==0&&b%i==0)
			g=i;
	return gcd(i+1,g);
}
void main()
{
	int g=1;
	scanf("%d%d",&a,&b);
	a=abs(a); b=abs(b);
	(a>=b)?(l=b):(l=a);
	g=gcd(1,g);
	printf("%d",g);
}
	
