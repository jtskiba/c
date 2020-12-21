
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // needed for INT_MIN
#include <stdbool.h> //need this to recognise bool type, otherwise it is _Bool

/* Skiena section 5.8, p.169

Problem: Implementation of depth first search - recursive (otherwise, same as bfs just use stack instead of queue)
includes:
- finding cycles 5.9.1 (p.173) <-- done in this script
- strongly connected components 

*/

// below is the graph representation adjacency list, with some BFS specific updates

#define MAXV 1000 //max no of vertices

typedef struct edgenode {
	int y;
	int weight;	
	struct edgenode *next;
} edgenode;

typedef struct graph {
	edgenode *edges[MAXV+1];
	int degree[MAXV+1];
	int nvertices;
	int nedges;
	bool directed;
		
} graph;


void initialize_graph(graph *g, bool directed){
	int i;
	
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;
	
	for (i=1;i<=MAXV;i++) g->degree[i] = 0;
	for (i=1;i<=MAXV;i++) g->edges[i] = NULL;
}

void insert_edge(graph *g, int x, int y, bool directed){
	edgenode *p;
	p = malloc(sizeof(edgenode));
	
	p->y = y;
	p->weight = 1; //dummy - all same weight here
	p->next = g->edges[x];
	
	g->edges[x] = p;
	g->degree[x] ++;
	
	if (directed == false)
		insert_edge(g, y, x, true);
	else
		g->nedges ++;
}

void read_graph(graph *g, bool directed){
	int i; //counter
	int m; //number of edges
	int x, y; //vertices in edge (x,y)
	
	initialize_graph(g, directed);
	scanf("%d %d", &(g->nvertices), &m);
	
	for (i=1; i<=m; i++){
		scanf("%d %d", &x, &y);
		insert_edge(g, x, y, directed);
	}
}


void print_graph(graph *g){
	int i;
	edgenode *p;
	
	for (i=1;i<=g->nvertices; i++){
		printf("%d: ",i);
		p = g->edges[i];
		while (p != NULL){
			printf(" %d",p->y);
			p = p->next;
		}
		printf("\n");
	}
}

// below adding BFS ones: - seen globally, hence outside main
bool processed[MAXV+1];  //which vertices have been processed, i.e. all routes from it examined
bool discovered[MAXV+1]; //which vertices have been found/discovered, i.e. not all routes from it examined yet
int parent[MAXV+1];   //discovery relation // for depth first recursive 

int entry_time[MAXV+1]; // for depth first recursive 
int exit_time[MAXV+1];  // for depth first recursive 
int time = 0;           // for depth first recursive 
bool finished = false; // for depth first recursive 

void initialize_search(graph *g){
	int i;
	for (i=1; i<=g->nvertices; i++){
		processed[i] = discovered[i] = false;
		parent[i] = -1;
	}
}


//below 3 functions can be filled in as needed
void process_vertex_early(int v){
	//
	printf("Vertex: %d\n", v);
}

void process_vertex_late(int v){
	
}

// this is for finding cycles - Skiena 5.9.1 p.173
void process_edge(int x, int y){
	printf("Processing edge (%d %d)\n",x,y);
}

// traversal below
void dfs(graph *g, int v){
		
	int y;       // successor vertex
	edgenode *p; // temp pointer
	
	if (finished) return; // allow for search termination
	
	discovered[v] = true;
	time++;
	entry_time[v] = time;
	
	process_vertex_early(v);		

	p = g->edges[v];
	while (p != NULL){
		y = p->y;
		if (discovered[y] == false){
			parent[y] = v;
			process_edge(v, y);
			dfs(g, y);
		}
		else if ((!processed[y]) || (g->directed))
			process_edge(v, y);
		
		if (finished) return;
		p = p->next;
	}
	process_vertex_late(v);
	time++;
	exit_time[v] = time;
	processed[v] = true;
}



int main(void){
	
	graph g;
	bool directed = false;
		
	read_graph(&g, directed);
	print_graph(&g);
	
	dfs(&g, 1);

	/* baby example for dfs
3 3
1 2
2 3
1 3

	*/
	return 0;
}