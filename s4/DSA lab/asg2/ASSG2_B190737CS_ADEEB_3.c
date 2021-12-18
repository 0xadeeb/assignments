#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include<math.h>

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

int value(char* word)
{
	int sum = 0;	
	bool chars[8];
	for(int i =0 ; i <8; i++)
		chars[i] = false;
		
	for( int i = 0; i< strlen(word); i++)
		chars[(int)(word[i])-97] = true;
		
	for(int i =0 ; i <8; i++)
		if(chars[i])
			sum += pow(2, i);
	return sum;
}

void insert_head(node** head, node* w)
{
	node* temp = *head;
	*head = w;
	w->next = temp;
}

void insert_after(node* pos, node* w)
{
	node* temp = pos->next;
	pos->next = w;
	w->next = temp;
}

void map(node** hashmap, char* word)
{
	int i = value(word);
	node* pos = hashmap[i], *w = create_node(word);
	
	if(hashmap[i] == NULL)
		hashmap[i] = w;
	
	else
	{
		if(strcmp(word,pos->word) == 0)
			return;
		if(strcmp(word,pos->word) < 0)
		{
			insert_head(&hashmap[i],w);
			return;
		}
		while(pos->next != NULL)
		{
			if( strcmp(word,pos->word) > 0 && strcmp(word,(pos->next)->word) < 0)
			{
				insert_after(pos,w);
				return;
			}
			pos = pos->next;
		}
		
		pos->next = w;
	}
}

void print( node** hashmap)
{
	node* t;
	for(int i=0; i<255; i++)
	{
		t = hashmap[i];
		if(t==NULL)
			continue;
		while(t!=NULL)
		{
			printf("%s ", t->word);
			t = t->next;
		}
		printf("\n");
	}
}	
	
void main()
{
	int n;
	char *word = (char*)malloc(52*sizeof(char));
	node** hashmap = (node**)calloc(255,sizeof(node*));
	scanf("%d",&n);
	
	for(int i = 0; i< n; i++)
	{
		scanf("%s",word);
		map(hashmap,word);
	
	}
	
	print(hashmap);
}
	
