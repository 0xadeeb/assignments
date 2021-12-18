#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<math.h>

long modulo(long base, long exponent, long mod) 
{
    long x = 1, y = base;

    while (exponent > 0) 
    {
	if (exponent % 2 == 1)
		x = (x * y) % mod;

        y = (y * y) % mod;
	exponent = exponent / 2;

    }

    return x % mod;

}

bool isPrime(long p)
{

    int i;

    if (p == 1) 
    	return false;

    for (i = 0; i < 50; i++) 
    {

        long a = rand() % (p - 1) + 1;

        if (modulo(a, p - 1, p) != 1) 
        	return false;

    }

    return true;

}

int smallest_pno(int m)
{
	for(int i = m-1; i > 1; i--)
		if(isPrime(i))
			return i;
}

void insert_quad(double key, int c1, int c2, int m, double* arr)
{	
	//printf("hi\n");
	int h1 = (int)key%m, pos;
	
	for(int i = 0; i<m; i++)
	{
		pos = (h1+ i*c1 + i*i*c2)%m;
		
		if(arr[pos] == 2.5)
		{
			arr[pos] = key;
			return;
		}
	}
}

void insert_double(double key , int r, int m, double* arr)
{
	int h1 = (int)key%m,  h2 = r - ((int)key%r), pos;
	
	for(int i = 0; i<m; i++)
	{
		pos = ( h1 + i*h2)%m;
		
		if(arr[pos] == 2.5)
		{
			arr[pos] = key;
			return;
		}
	}
}
	
double search_quad(double key, int c1, int c2, int m, double* arr)
{
	int h1 = (int)key%m, pos;
	
	for(int i = 0; i<m; i++)
	{
		pos = (h1+ i*c1 + i*i*c2)%m;
		
		if(arr[pos] == key)
			return pos;
	}
	
	return -1;
}

double search_double(double key, int r, int m, double* arr)
{
	
	int h1 = (int)key%m, h2 = r - ((int)key%r), pos;
	
	for(int i = 0; i<m; i++)
	{
		pos = ( h1 + i*h2)%m;
		
		if(arr[pos] == key)
			return pos;
	}
	
	return -1;
}	

void del_quad(double key, int c1, int c2, int m, double* arr)
{
	int pos = search_quad(key,c1,c2,m,arr);
	
	if(pos != -1)
		arr[pos] = 2.5;
}

void del_double(double key, int r, int m, double* arr)
{
	int pos = search_double(key,r,m,arr);
	
	if(pos != -1)
		arr[pos] = 2.5;
		
}
		
void print(double *arr, int m)
{
	for( int i = 0; i<m; i++)
	{
		if(arr[i]!=2.5)
			printf("%d (%d)\n", i,(int)arr[i]);
		else
			printf("%d ()\n", i);
	}
}

void main()
{
	char opt1,opt2;
	int m,c1,c2, h1,h2, r;
	double key, *arr;
	scanf("%c",&opt1);
	scanf("%d",&m);
	arr = (double*)malloc(m*sizeof(double));
		
	for(int i =0 ; i<m; i++)
		arr[i] = 2.5;
	
	switch(opt1)
	{
		case 'a':
			scanf("%d %d",&c1,&c2);
			scanf("%c",&opt2);
			while(opt2!='t')
			{
				switch(opt2)
				{ 
					case 'i': 
						scanf("%lf",&key);
						insert_quad(key,c1,c2,m,arr);
						break;
					case 's':
						scanf("%lf",&key);
						if(search_quad(key,c1,c2,m,arr)!=-1)
							printf("1\n");
						else
							printf("-1\n");
						break;
					case 'd':
						scanf("%lf",&key);
						del_quad(key,c1,c2,m,arr);
						break;
					case 'p':
						print(arr,m);
						break;
				}
				scanf("%c",&opt2);
			}
			break;
			
		case 'b':
			r = smallest_pno(m);
			scanf("%c",&opt2);
			while(opt2!='t')
			{
				switch(opt2)
				{ 
					case 'i': 
						scanf("%lf",&key);
						insert_double(key,r,m,arr);
						break;
					case 's':
						scanf("%lf",&key);
						if(search_double(key,r,m,arr)!=-1)
							printf("1\n");
						else
							printf("-1\n");
						break;
					case 'd':
						scanf("%lf",&key);
						del_double(key,r,m,arr);
						break;
					case 'p':
						print(arr,m);
						break;
				}
				scanf("%c",&opt2);
			}
			break;
	}
}
			
		
				
						
