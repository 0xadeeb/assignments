#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct cst
{
	int acc_no;
	char name[25];
	float balance;
}cst;

void cpy(cst* a,cst *b)
{
	a->acc_no = b->acc_no;
	strcpy(a->name, b->name);
	a->balance = b->balance;
}

void read_and_store(cst* c, int n)
{	
	for(int i = 0 ; i< n ; i++)
		scanf("%d%s%f",&c[i].acc_no, c[i].name, &c[i].balance);
}

void sort_record(cst * c, int n)
{
	cst *temp = (cst*)malloc(sizeof(cst));
	int j;
	for( int i = 1; i<n ; i ++)
	{
		cpy(temp, &c[i]);
		j = i -1;
		while( j>=0 && c[j].acc_no > temp->acc_no)
		{
			cpy(&c[j+1],&c[j]);
			j--;
		}
		cpy(&c[j+1],temp);
	}
}

int search_record(cst* c, int a, int n)
{
	for( int i = 0; i<n; i++)
		if( c[i].acc_no == a)
			return i;
	return -1;
}

void display( cst * c, int n)
{
	for( int i = 0 ; i< n; i++)
		printf("%d %s %.2f\n",c[i].acc_no,c[i].name,c[i].balance);
}

void main()
{
	int n,a,q;
	char opt;
	cst* c;
	scanf("%c",&opt);
	while(opt != 'e')
	{
		switch(opt)
		{
			case 'r': 
				scanf("%d",&n);
				c = (cst*)malloc(n* sizeof(cst));
				read_and_store(c,n);
				break;
			case 's':
				sort_record(c,n);
				break;
			case 'f':
				scanf("%d",&a);
				q=search_record(c,a,n);
				printf("%d\n",q);
				break;
			case 'd':
				display(c,n);
		}
		scanf("%c",&opt);
	}
}
			
