#include<stdio.h>
#include<stdlib.h>

typedef struct movie
{
	float rating;
	char name[20];
} movie;

typedef struct frequency
{
	int fr;
	float value;
} frequency;

int cmp( const void *a, const void *b)
{
	frequency *A = (frequency*)a;
	frequency *B = (frequency*)b;
	return A->fr - B->fr;
}

void store_db(movie* db, int n)
{
	for(int i=0; i<n; i++)
		scanf("%s%f", db[i].name, &db[i].rating);
}

void list_db(movie* db, int n)
{
	for(int i=0; i<n; i++)
		printf("%s %.1f\n", db[i].name, db[i].rating);
}

void  popular_rating(movie *db, int n)
{
	frequency *f= (frequency*)malloc(sizeof(frequency));
	int c=0;
	for(int i =0; i<n; i++)
	{
		int cnd=0;
		for(int k=0; k<c; k++)
			if(db[i].rating== f[k].value)
				{cnd = 1;break;}
		if (cnd)
			continue;
		
		f = (frequency*)realloc(f, ++c * sizeof(frequency));
		f[c].fr=0;
		f[c].value= db[i].rating;
		for(int j= i+1; j<n; j++)
			if( db[j].rating == f[c].value)
				f[c].fr++;
	}
	
	qsort(f,c, sizeof(frequency), cmp);
	
	float max=f[0].value;
	
	for(int i=0; i<c-1; i++)
	{	
		if(f[i].fr == f[i+1].fr)
			if(max<f[i+1].value)
				max = f[i].value;
		else
			break;
	}
	
	printf("%f\n",max);
}

	



void main()
{
	movie *e,*h,*m;
	char opt;
	int n,no,r;
	scanf("%d%c",&n,&opt);
	
	e =(movie*)malloc(n*sizeof(movie));
	h =(movie*)malloc(n*sizeof(movie));
	m =(movie*)malloc(n*sizeof(movie));
	
	while (opt != 't')
	{
		switch (opt)
		{
			case 's': scanf("%d",&no);
				if(no ==1)
					store_db(e,n);
				if(no ==2)
					store_db(h,n);
				if(no ==3)
					store_db(m,n);
				break;
				
			case 'l': scanf("%d",&no);
				if(no ==1)
					list_db(e,n);
				if(no ==2)
					list_db(h,n);
				if(no ==3)
					list_db(m,n);
				break;
				
			case 'p': scanf("%d",&no);
				if(no ==1)
					popular_rating(e,n);
				if(no ==2)
					popular_rating(h,n);
				if(no ==3)
					popular_rating(m,n);
				break;
			case 'b': scanf("%d",&r);
				//printf("%d",best_r(e,h,m,n,r));
				break;
		}
		scanf("%c",&opt);
	}
			
			
}			
			
