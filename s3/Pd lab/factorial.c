#include <stdio.h>
#include <math.h>
#include <string.h>
void main()
{
	char word[30];
	strcpy(word,"abcdefghij");
	for(int i = 0; i< 10; i++)
		printf("%d ",(int)(word[i])-97);
	
	printf("\n");
}
	
