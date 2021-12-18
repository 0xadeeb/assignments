#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void main()
{
	FILE* fp_read, *fp_write;
	fp_read = fopen("input.txt","r");
	fp_write = fopen("output.txt", "w");
	
	char exp[10000];
	int ch;
	
	while((ch= fgetc(fp_read))!=EOF)
		for(int i= 0 ; (char)ch =! "\n"; i++)
			exp[i] = ch;
	
