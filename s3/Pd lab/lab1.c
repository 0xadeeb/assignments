#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student
{
	char name[20];
	float grade;
} student;

void swap(student *a, student *b)
{
	student temp;
	temp.grade = a->grade;
	a->grade= b->grade;
	b->grade= temp.grade;
	strcpy(temp.name, a->name);
	strcpy(a->name, b->name);
	strcpy(b->name, temp.name);
}

void combine(student *l, student* r, int n1, int n2)
{
	int size = n2+1;
	for(int i=0; i<n1; i++)
		for(int j= 0; j<size; j++)
		{
			if(l[i].grade<r[j].grade)
			{
				swap(l+i,r+j);
				j++;
				while(j<size)
				{
					swap(l+i,r+j);
					j++;
				}
				size++;
				continue;
			}
			if(j== size-1)
			{
				r[j].grade = l[i].grade;
				strcpy(r[j].name,l[i].name);
			}
		}
			
}

void main()
{
	int n1,n2;
	student *l,*r;
	scanf("%d",&n1);
	scanf("%d",&n2);
	l = (student*)malloc(n1*sizeof(student));
	r = (student*)malloc((n1+n2)*sizeof(student));
	for(int i=0; i<n1; i++)
		scanf("%s%f",l[i].name,&l[i].grade);
	for(int i=0; i<n2; i++)
		scanf("%s%f",r[i].name,&r[i].grade);
		
	combine(l,r,n1,n2);
	printf("\n");	
	for(int i=0; i<(n2+n1); i++)
		printf("%s %.2f \n",r[i].name,r[i].grade);
	
}
	
	
