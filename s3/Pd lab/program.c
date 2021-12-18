#include<stdio.h>
void main()
{

	int x=3, y=0, z=1;
	printf("%d %d %d\n", x&&y,y&&z,z&&x);
	printf("%d %d %d\n", x||y,y||z,z||x);
	
}
