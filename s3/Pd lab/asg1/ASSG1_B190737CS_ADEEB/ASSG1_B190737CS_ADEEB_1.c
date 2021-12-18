#include<stdio.h>
#include<stdlib.h>
void main()
{
	int n, *a, ele, present = 0, error;
	
	error = scanf("%d",&n);
	if(!error)
		printf("Error not a digit");
	else
	{
		a = (int*)malloc(n * sizeof(int));
		
		int digit =1;
		for(int i=0; i<n; i++)
			error=error&&scanf("%d",(a+i));
		if(!error)
			printf("Error not a digit");
		else
		{
			
			error=scanf("%d",&ele);
			if(!error)
				printf("Error element not a digit");
			else
			{
				for(int i=0; i<n; i++)
					if(*(a+i)==ele)
					{	
						printf("%d ",i);
						present = 1;
					}
				if(!present)
					printf("-1");
			}
		}
	}
	//printf("\n");
}
