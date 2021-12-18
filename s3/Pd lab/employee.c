#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct employee
{
	char name[10];
	int salary, working_time, no_of_leaves;
}e[10];

int i=0;

void insert()
{
	scanf("%s",e[i].name);
	scanf("%d",&e[i].salary);
	scanf("%d",&e[i].working_time);
	scanf("%d",&e[i].no_of_leaves);
	if(e[i].working_time>10)
		e[i].salary+=150;
	else if(e[i].working_time==10)
		e[i].salary+=100;
	else if(e[i].working_time>=8)
		e[i].salary+=50;
	i++;
}

int compute_deductions(char* ename)
{
	for(int j=0; j<i; j++)
		if(strcmp(ename, e[j].name)==0)
		{
			if(e[j].no_of_leaves>5)
				return 1000*(e[j].no_of_leaves-5);
			else
				return 0;
		}
}

void print_no_increment()
{
	for(int j=0; j<i; j++)
		if(e[j].working_time<8)
			printf("%s %d\n",e[j].name, e[j].salary);
}

void print_final_salary()
{
	for(int j=0; j<i; j++)
		printf("%s %d\n", e[j].name, e[j].salary);
}

void print_work_perday(int w)
{
	for(int j=0; j<i; j++)
		if(e[j].working_time==w)
			printf("%s %d\n",e[j].name, e[j].salary);
}
	

void main()
{
	char option, ename[10];
	int w;
	scanf("%c",&option);
	while(option!='t')
	{
		switch (option)
		{
			case 'r': insert();
			break;
			case 'i': print_no_increment();
			break;
			case 'f': print_final_salary();
			break;
			case 'w': 
			scanf("%d",&w); 
			print_work_perday(w);
			case 'd':
			scanf("%s",ename);
			printf("%d\n",compute_deductions(ename));
			break;
		}
		scanf("%c",&option);
	}
}
