#include<stdio.h>
#include<stdlib.h>

int tot_size;
char colors[7] = "abcdef";

int no_adj_color(int** graph, char *vertices, int selected_vertex, char color)
{
	for(int i=0; i<tot_size; i++)
		if(graph[i][selected_vertex] && vertices[i]==color)
			return 0;
	return 1;
}
	
void color_graph(int **graph, char *vertices, int n)
{
	int selected_vertex;
	if(n==1)
	{
		for(int i=0;i<tot_size;i++)
			if(graph[i][i]==1)
			{	selected_vertex=i;
				break;
			}
		vertices[selected_vertex]='a';
	}
	else
	{
		int sum, **temp;
		temp=(int**)malloc(tot_size*sizeof(int*));
		for(int i=0; i<tot_size; i++)
			temp[i]= (int*)calloc(i+1,sizeof(int));
		
		for(int i=0; i<tot_size; i++)
		{
			sum=0;
			for(int j=0; j<=i; j++)
				sum+=graph[i][j];
				
			if(sum!=0&&sum<6)
			{
				selected_vertex=i;
				break;
			}
		}
		
		for(int i=0; i<tot_size; i++)
			for(int j=0; j<=i; j++)
				if(j!=selected_vertex&&i!=selected_vertex)
					temp[i][j]= graph[i][j];
		
		color_graph(temp,vertices,n-1);
				
		for(int i=0; i<7; i++)
			if(no_adj_color(graph, vertices, selected_vertex, colors[i]))
				{vertices[selected_vertex]=colors[i];break;}
		
		free(temp);
	}
				
}
		

void main()
{
	int n, e, **graph;
	char *vertices;
	scanf("%d %d",&n,&e);
	tot_size = n;
	graph= (int**)malloc(n*sizeof(int*));
	vertices = (char*)malloc(n*sizeof(char));
	for(int i=0; i<n; i++)
		graph[i]= (int*)calloc(i+1,sizeof(int));
	for(int i=0; i<n; i++)
	{	
		vertices[i] = 'x';
		graph[i][i]=1;
	}
	for(int k=0; k<e; k++)
	{
		int j,i;
		scanf("%d %d", &i, &j);
		i>j?(graph[i][j]=1):(graph[j][i]=1);
	}
	color_graph(graph, vertices, n);
	
	
	for(int i=0; i<n; i++)
		printf("%c\n",vertices[i]);
	for(int i=0; i<n; i++)
		free(graph[i]);
	free(graph);free(vertices);

}
