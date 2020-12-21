
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // needed for INT_MIN
#include <stdbool.h> //need this to recognise bool type, otherwise it is _Bool

/* Skiena Chapter 6 - Weighted graphs, 3 algos are covered:
- 6.1 Minimum spanning tree (prim's algo, kruskal's algo with union-find data structure)
- 6.3 Shortest Paths (Dijkstra's algo, Floyd's all-pairs shortest path)
- 6.5 Maximum flow (i.e. Network flows and bipartite matching)
*/

//// KRUSKAL'S ALGO with union-find


// below is the graph representation adjacency list, with some BFS specific updates

#define MAXV 100 //max no of vertices
#define SET_SIZE 100 //max no of vertices in the set

//DFS
bool processed[MAXV+1];  //which vertices have been processed, i.e. all routes from it examined
bool discovered[MAXV+1]; //which vertices have been found/discovered, i.e. not all routes from it examined yet
int parent[MAXV+1];   //discovery relation // for depth first recursive 

int entry_time[MAXV+1]; // for depth first recursive 
int exit_time[MAXV+1];  // for depth first recursive 
int time = 0;           // for depth first recursive 
bool finished = false; // for depth first recursive 

// QUEUE start

//BFS will also need a queue data structure, copied below
typedef struct queue{ // from: https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/
	int front, rear, size;
	unsigned capacity;
	int *array;
} queue;

queue *createQueue(unsigned capacity)
{
	queue *this_queue = (queue *) malloc(sizeof(queue));
	this_queue->capacity = capacity;
	this_queue->front = this_queue->size = 0;
	this_queue->rear = capacity - 1; //important - see enqueue
	this_queue->array = (int *) malloc(this_queue->capacity * sizeof(int));
	return this_queue;
}

// queue becomes full when size becomes equal to the capacity
int isFull(queue *this_queue){
	return(this_queue->size == this_queue->capacity);
}

// queue is empty when size is 0
int isEmpty(queue *this_queue){
	return (this_queue->size == 0);
}

//Function to add item to a queue, it changes rear and size
void enqueue(queue *this_queue, int item){
	if (isFull(this_queue))
		return;
	this_queue->rear = (this_queue->rear + 1)%this_queue->capacity;
	this_queue->array[this_queue->rear] = item;
	this_queue->size = this_queue->size + 1;
	//printf("%d enqueued to queue\n", item);
}

int dequeue(queue *this_queue){
	if (isFull(this_queue))
		return INT_MIN;
	int item = this_queue->array[this_queue->front];
	this_queue->front = (this_queue->front + 1)%this_queue->capacity;
	this_queue->size = this_queue->size - 1;
	return item;
}

//Function to get front of queue
int front(queue *this_queue){
	if(isEmpty(this_queue))
		return INT_MIN;
	return (this_queue->array[this_queue->front]);
}

//Function to get rear of queue
int rear(queue *this_queue){
	if(isEmpty(this_queue))
		return INT_MIN;
	return (this_queue->array[this_queue->rear]);
}
// QUEUE end


// GRAPH tools...
typedef struct edgenode {
	int y;
	int weight;	// for weighted graphs!
	struct edgenode *next;
} edgenode;

typedef struct graph {
	edgenode *edges[MAXV+1];
	int degree[MAXV+1];
	int nvertices;
	int nedges;
	bool directed;
		
} graph;

/// new for kruskal - own
typedef struct edge_pair {
	int x; //head of the edge
	int y; //back of the edge
	int weight;	// for weighted edges
} edge_pair;


typedef struct set_union {
	int p[SET_SIZE+1];    // parent of the set element
	int size[SET_SIZE+1]; // size of subtree of the set element, ie no of elts in subtree i
	int n; 				  // size of tree (nvertices) ie no of elts in this set
} set_union;

// union-find functions
void set_union_init(set_union *s, int n){
	int i;
	for (i=1; i<=n; i++){
		s->p[i] = i;
		s->size[i] = 1;
	}
	s->n = n;
}
 
int find(set_union *s, int x){
	if (s->p[x] == x)
		return x;
	else
		return( find(s, s->p[x]) );
}

void union_sets(set_union *s, int s1, int s2){
	int r1, r2; //roots of s1 and s2
	r1 = find(s, s1);
	r2 = find(s, s2);
	if (r1==r2)
		return; //already in the same connected component, do nothing
	if (s->size[r1] >= s->size[r2]){
		s->size[r1] = s->size[r1] + s->size[r2];
		s->p[r2] = r1;
	}
	else {
		s->size[r2] = s->size[r1] + s->size[r2];
		s->p[r1] = r2;
	}
}

bool same_component(set_union *s, int s1, int s2){
	return( find(s, s1) == find(s,s2) );
}

// GRAPHS
void initialize_graph(graph *g, bool directed){
	int i;
	
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;
	
	for (i=1;i<=MAXV;i++) g->degree[i] = 0;
	for (i=1;i<=MAXV;i++) g->edges[i] = NULL;
}

// modifified to include weight
void insert_edge(graph *g, int x, int y, int weight, bool directed){
	edgenode *p;
	p = malloc(sizeof(edgenode));
	
	p->y = y;
	p->weight = weight; // changed from 1
	p->next = g->edges[x];
		
	g->edges[x] = p;
	g->degree[x] ++;
	
	if (directed == false)
		insert_edge(g, y, x, weight, true);
	else
		g->nedges ++;
}

void read_graph(graph *g, bool directed){
	int i; //counter
	int m; //number of edges
	int x, y; //vertices in edge (x,y)
	int weight; // weight of the edge (x, y)
	
	initialize_graph(g, directed);
	scanf("%d %d", &(g->nvertices), &m);
	
	for (i=1; i<=m; i++){
		scanf("%d %d %d", &x, &y, &weight);
		insert_edge(g, x, y, weight, directed);
	}
}

void print_graph(graph *g){
	int i;
	edgenode *p;
	
	for (i=1;i<=g->nvertices; i++){
		printf("%d: ",i);
		p = g->edges[i];
		while (p != NULL){
			printf(" %d(%d)",p->y,p->weight);
			p = p->next;
		}
		printf("\n");
	}
}
// END GRAPH tools


void process_vertex_early(int v){
	//printf("Vertex: %d\n", v);
}

void process_vertex_late(int v){
	//
}

void process_edge(int x, int y, int weight, edge_pair *e, int *count){
	int loc_count;
	(*count)++;
	loc_count = (*count);
	printf("count=%d\n",loc_count);
	e[loc_count].x = x;
	e[loc_count].y = y;
	e[loc_count].weight = weight;
	
	printf("-> x=%d, y=%d, w=%d\n", x, y, weight);
	
	//printf("Processing edge (%d %d)\n",x,y);
}


// traversal below
void bfs(graph *g, int start, edge_pair *e, int *count){
		queue *q;     // queue of vertices to visit
		int v;       // current vertex that we are processing
		int y;       // successor vertex
		int weight;  // weight of the edge
		edgenode *p; // temp pointer
		
		q = createQueue(MAXV+1);
		enqueue(q, start);
		discovered[start] = true;
		
		while (isEmpty(q) != 1){
			//printf("\n---\n");
			v = dequeue(q);
			process_vertex_early(v);
			processed[v] = true;
			p = g->edges[v];
			while (p != NULL){
				y = p->y;
				weight = p->weight;
				if ((processed[y] == false) || g->directed)
					process_edge(v, y, weight, e, count);
				if (discovered[y] == false){
					enqueue(q, y);
					discovered[y] = true;
					parent[y] = v;
				}
				p = p->next;
			}
			process_vertex_late(v);
		}
}


void to_edge_array(graph *g, edge_pair *edge){
	int start = 1;
	int count = 0;
	//printf("\nhere1\n");
	bfs(g, start, edge, &count);
	
}

int weight_compare(const void *a, const void *b){
	//ascending order of weights
	edge_pair *A = (edge_pair *)a;
	edge_pair *B = (edge_pair *)b;
	
	return (A->weight - B->weight);
}

void kruskal(graph *g){
	int i;					//counter
	set_union s;			//set union data structure
	edge_pair ep[MAXV+1];    //array of edges data structure
	int weight_compare();
	
	set_union_init(&s, g->nvertices);
		
	to_edge_array(g, ep);
	qsort(&ep,g->nedges, sizeof(edge_pair), weight_compare);
	
	for (i=1; i<=(g->nedges); i++){
		if (!same_component(&s, ep[i].x, ep[i].y)){
			printf("edge (%d %d) in MST\n", ep[i].x, ep[i].y);
			union_sets(&s, ep[i].x, ep[i].y);
		}
	}
}


int main(void){
	
	int i;
	graph g;
	edge_pair e[10];
	bool directed = false;
	
	read_graph(&g, directed);
	kruskal(&g);
	
// baby example - taken from Skiena p.196 where A=1, B=2, C=3, D=4, E=5, F=6, G=7

/*
3 3
1 2 4
1 3 5
2 3 6
*/

// first row #V #END// then next rows are #V1 #V2 weight
//larger one from Skiena p.196
/*
7 12
1 2 5
1 5 12
1 4 7
2 4 9
2 3 7
3 4 4
3 7 5
3 6 2
4 6 3
4 5 4
5 6 7
6 7 2
*/		
	
	return 0;
}