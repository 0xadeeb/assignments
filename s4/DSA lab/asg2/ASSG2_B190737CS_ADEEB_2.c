#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

typedef struct node
{
	char* word;
	struct node* next;
} node;

node* create_node(char* word)
{
	node* n = (node*)malloc(sizeof(node));
	n->word = (char*)malloc(strlen(word)*sizeof(char));
	strcpy(n->word, word);
	n->next = NULL;
	return n;
}

void map(node** hashmap, char* word, int k)
{
	int len = strlen(word);
	int pos = (len*len)%k;
	node* w = create_node(word),*t = hashmap[pos];
	
	if(hashmap[pos] == NULL)
		hashmap[pos] = w;
	else
	{
		while( t->next!= NULL)
		{
			if( strcmp(t->word,word) == 0)
				return;
			t = t->next;
		}
		
		if( strcmp(t->word,word) == 0)
			return;
		
		t->next = w;
	}
}

void print(node** hashmap, int k)
{
	node* h;
	
	for( int i = 0 ; i< k; i++)
	{
		printf("%d:",i);
		h = hashmap[i];
		if(h==NULL)
			printf("null");
		while(h!=NULL)
		{
			if(h->next != NULL)
				printf("%s-", h->word);
			else
				printf("%s", h->word);
			h = h->next;
		}
		printf("\n");
	}
}

void main()
{
	char* word = (char*)malloc(sizeof(char)*52),c='i';
	int k,i;
	scanf("%d",&k);
	scanf("\n");
	node** hashmap = (node**)calloc(k,sizeof(node*));

	
	while(c!='\n')
	{
		i=0;
		scanf("%c",&c);
		while(isalpha(c))
		{
			word[i++] = c;
			scanf("%c",&c);
		}
		
		word[i] = '\0';
		
		map(hashmap,word,k);
	}
	
	print(hashmap,k);
}
	
	
	
