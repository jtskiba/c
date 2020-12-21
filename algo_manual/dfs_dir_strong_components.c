
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // needed for INT_MIN
#include <stdbool.h> //need this to recognise bool type, otherwise it is _Bool

/* Skiena section 5.8, p.169

Problem: Implementation of depth first search - recursive (otherwise, same as bfs just use stack instead of queue)
includes:
- finding cycles 5.9.1 (p.173) 
- articulation vertices 5.9.2 (p.173)
- topological sorting (for directed graphs) 5.10.1 (p.179)
- strongly connected components (for directed graphs) 5.10.2 (p.181) <-- done in this script

*/

// below is the graph representation adjacency list, with some BFS specific updates

#define MAXV 1000 //max no of vertices

//below for articulation vertices
#define TREE 0
#define BACK 1
#define FORWARD 2 // for directed graphs only
#define CROSS 3   // for directed graphs only

// STACK for strong components


typedef struct stack{ // from: https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
	int top;
	unsigned capacity;
	int *array;
} stack;

stack *createStack(unsigned capacity)
{
	stack *this_stack = (stack *) malloc(sizeof(stack));
	this_stack->capacity = capacity;
	this_stack->top = -1;
	this_stack->array = (int *) malloc(capacity * sizeof(int));
	return this_stack;
}


// stack is empty when top is -1
int isNull(stack *this_stack){
	return (this_stack->top == -1);
}

//Function to add item to a queue, it changes rear and size
void push(stack *this_stack, int item){
	this_stack->top = (this_stack->top + 1);
	this_stack->array[this_stack->top] = item;
	//printf("%d pushed to stack\n", item);
}

int pop(stack *this_stack){
	if (isNull(this_stack))
		return INT_MIN;
	int item = this_stack->array[this_stack->top];
	this_stack->top = (this_stack->top - 1);
	return item;
}

//Function to get front of queue
int top(stack *this_stack){
	if(isNull(this_stack))
		return INT_MIN;
	return (this_stack->array[this_stack->top]);
}

void print_stack(stack *this_stack){
	while (!isNull(this_stack))
		printf("%d ", pop(this_stack));
	printf("\n");
}

// END OF STACK

// GRAPH tools...

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
// END GRAPH tools


// below adding BFS/DFS ones: - seen globally, hence outside main
bool processed[MAXV+1];  //which vertices have been processed, i.e. all routes from it examined
bool discovered[MAXV+1]; //which vertices have been found/discovered, i.e. not all routes from it examined yet
int parent[MAXV+1];   //discovery relation // for depth first recursive 

// adding DFS specific
int entry_time[MAXV+1]; // for depth first recursive 
int exit_time[MAXV+1];  // for depth first recursive 
int time = 0;           // for depth first recursive 
bool finished = false; // for depth first recursive

// for articulation vertices
int reachable_ancestors[MAXV+1];// earliest reachable ancestor of v
int tree_out_degree[MAXV+1];	// DFS tree outdegree of v 

// for strongly connected components SCC (also needed for topological sorting, just call it 'sorted'
stack *active;

// for SCC
int low[MAXV+1];   //oldest vertex surely in component v
int scc[MAXV+1];   //strong component number for each vertex 
int components_found;

void initialize_search(graph *g){
	int i;
	for (i=1; i<=g->nvertices; i++){
		processed[i] = discovered[i] = false;
		parent[i] = -1;
	}
}


//below 3 functions can be filled in as needed
void process_vertex_early(int v){
	push(active, v);		
}

void pop_component(int v){
	int t;    // vertex placeholder
	components_found++;
	
	scc[v] = components_found;
	
	while ((t = pop(active)) != v){
		scc[t] = components_found;
	}
}

void process_vertex_late(int v){
	if (low[v] == v){   //edge (parent[v],v) cuts off SCC
		pop_component(v);
	}
	if (entry_time[low[v]] < entry_time[low[parent[v]]])
		low[parent[v]] = low[v];
	
}


int edge_classification(int x, int y){
	if (parent[y] == x) return(TREE);
	if (discovered[y] && !processed[y]) return(BACK);
	if (processed[y] && (entry_time[y]>entry_time[x])) return(FORWARD);   // for directed graphs only
	if (processed[y] && (entry_time[y]<entry_time[x])) return(CROSS);     // for directed graphs only
	
	printf("Warning: unclassified edge (%d %d)\n", x, y);
}

void find_path(int start, int end, int parents[]){
	if ((start==end) || (end==-1))
		printf("\n%d", start);
	else {
		find_path(start, parents[end],parents);
		printf("\n%d",end);
	}
}

// for SCC
void process_edge(int x, int y){
	int class;
	class = edge_classification(x, y);
	if (class == BACK){
		if (entry_time[y] < entry_time[ low[x] ])
			low[x] = y;			
	}
	
	if (class == CROSS){
		if (scc[y] == -1)   // component not yet assigned
			if (entry_time[y] < entry_time[ low[x] ])
				low[x] = y;			
	}
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

void strong_components(graph *g){
	int i;

	for (i=1; i<=(g->nvertices); i++){
		low[i] = i;
		scc[i] = -1;
	}
	components_found = 0;
	active = createStack(100);
	initialize_search(g);
	
	for (i=1; i<=(g->nvertices); i++)
		if (discovered[i] == false)
			dfs(g, i);
		
	for (i=1; i<=(g->nvertices); i++)
		printf("%d ", scc[i]);
	printf("\n");
}


int main(void){
	
	int i;
	graph g;
	bool directed = true;
	
	// for topological sorting
	
	
	read_graph(&g, directed);
	print_graph(&g);
	
	strong_components(&g);
	
	 
	

	/* baby example for dfs SCC, taken from p.182 of Skiena 5.10.2
8 12
3 1
1 2
2 3
4 1
2 4
4 8
4 6
2 5
5 6
7 5
6 7
8 6
	*/
	return 0;
}