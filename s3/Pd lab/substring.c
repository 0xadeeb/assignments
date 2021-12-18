#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int sub_check(char* a, char*b)
{
	int i=0,len = strlen(b);
	while(i<=strlen(a)-len)
	{
		int flag=1;
		for(int j=0; j<len; j++)
			if(a[i+j]!=b[j])
				{
					flag=0;
					break;
				}
		if(flag==1)
			return i;
		i++;
	}
	return -1;
}


void main()
{
	char *a= (char*)malloc(10000*sizeof(char)), *b= (char*)malloc(10000*sizeof(char));
	scanf("%[^\n]%*c",a);
	scanf("\n");
	scanf("%[^\n]%*c",b);
	a = (char*)realloc(a, strlen(a)*sizeof(char));
	b = (char*)realloc(b, strlen(b)*sizeof(char));
	printf("%d",sub_check(a,b));
	free(a);free(b);
}
