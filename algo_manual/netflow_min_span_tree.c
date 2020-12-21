// https://www3.cs.stonybrook.edu/~skiena/392/programs/netflow.c



#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // needed for INT_MIN
#include <stdbool.h> //need this to recognise bool type, otherwise it is _Bool
#include <math.h>

/* Skiena Chapter 6 - Weighted graphs, 3 algos are covered:
- 6.1 Minimum spanning tree (prim's algo, kruskal's algo with union-find data structure)
- 6.3 Shortest Paths (Dijkstra's algo, Floyd's all-pairs shortest path)
- 6.5 Maximum flow (i.e. Network flows and bipartite matching)  <---- done here
*/

//// NETWORK FLOW, p.218 Skiena


// below is the graph representation adjacency list, with some BFS specific updates

#define MAXV 100 //max no of vertices
#define SET_SIZE 100 //max no of vertices in the set

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

//BFS
bool processed[MAXV+1];  //which vertices have been processed, i.e. all routes from it examined
bool discovered[MAXV+1]; //which vertices have been found/discovered, i.e. not all routes from it examined yet
int  parent[MAXV+1];   //discovery relation // for depth first recursive 



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


// GRAPH tools... modifications for network flow
typedef struct edgenode {
	int y;      // neighbouring vertex
	int capacity;  //for networks
	int flow;  //for networks
	int residual;  //for networks	
	struct edgenode *next;
} edgenode;

typedef struct graph {
	edgenode *edges[MAXV+1];
	int degree[MAXV+1];
	int nvertices;
	int nedges;
	bool directed;
		
} graph;

void initialize_search(graph *g){
	int i;
	for (i=1; i<=g->nvertices; i++){
		processed[i] = discovered[i] = false;
		parent[i] = -1;
	}
}

void initialize_graph(graph *g, bool directed){
	int i;
	
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;
	
	for (i=1;i<=MAXV;i++) g->degree[i] = 0;
	for (i=1;i<=MAXV;i++) g->edges[i] = NULL;
}

// modifified to include capacity
void insert_edge(graph *g, int x, int y, int capacity, bool directed){
	edgenode *p;
	p = malloc(sizeof(edgenode));
	
	p->y = y;
	p->capacity = capacity;
	p->flow = 0;
	p->residual = p->capacity - p->flow;
	p->next = g->edges[x];
		
	g->edges[x] = p;
	g->degree[x] ++;
	
	if (directed == false)
		insert_edge(g, y, x, 0, true); // modified capacity to 0 to avoid using add_residual_edges
	else
		g->nedges ++;
}

void read_graph(graph *g, bool directed){
	int i; //counter
	int m; //number of edges
	int x, y; //vertices in edge (x,y)
	int capacity; // capacity of the edge (x, y)
	
	initialize_graph(g, directed);
	scanf("%d %d", &(g->nvertices), &m);
	
	for (i=1; i<=m; i++){
		scanf("%d %d %d", &x, &y, &capacity);
		insert_edge(g, x, y, capacity, directed);
	}
}

void print_graph(graph *g){
	int i;
	edgenode *p;
	
	for (i=1;i<=g->nvertices; i++){
		printf("%d: ",i);
		p = g->edges[i];
		while (p != NULL){
			printf(" %d(c:%d,f:%d,r:%d)",p->y, p->capacity, p->flow, p->residual);
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

void process_edge(int x, int y, int capacity){
	//printf("Processing edge (%d %d)\n",x,y);
}


bool valid_edge(edgenode *e){
	if (e->residual > 0) return(true);
	else return(false);
}

// traversal below
void bfs(graph *g, int start){
		queue *q;     // queue of vertices to visit
		int v;       // current vertex that we are processing
		int y;       // successor vertex
		int capacity;  // capacity of the edge
		edgenode *p; // temp pointer
		
		q = createQueue(MAXV+1);
		enqueue(q, start);
		discovered[start] = true;
		
		while (isEmpty(q) != 1){
			v = dequeue(q);
			process_vertex_early(v);
			processed[v] = true;
			p = g->edges[v];
			while ((p != NULL) && (valid_edge(p))){ //added the valid_edge
				y = p->y;
				capacity = p->capacity;
				if ((processed[y] == false) || g->directed)
					process_edge(v, y, capacity);
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


edgenode *find_edge(graph *g, int x, int y){
	edgenode *p; //temp
	p = g->edges[x];
	while (p != NULL){
		if (p->y == y) return(p);
		p = p->next;
	}
	return(NULL);
}

int path_volume(graph *g, int start, int end, int parents[]){
	edgenode *e;
	edgenode *find_edge();
	
	if (parents[end] == -1) return(0);
	
	e = find_edge(g, parents[end], end);
	
	if (start == parents[end])
		return(e->residual);
	else
		return( MIN(path_volume(g, start, parents[end], parents), e->residual) );
	
}

// not needed in my version as i am using undirected graphs and when inserting edges i automatically counter each edge with a backward one at 0 capacity
void add_residual_edges(graph *g){
	int i,j;			/* counters */

	for (i=1; i<=g->nvertices; i++) 
		for (j=0; j<g->degree[i]; j++)
			if (find_edge(g,g->edges[i][j].y,i) == NULL)
				insert_edge(g, g->edges[i][j].y, i, 0, true);
}

void augment_path(graph *g, int start, int end, int parents[], int volume){
	edgenode *e;
	edgenode *find_edge();
	
	if (start == end) return;
	
	e = find_edge(g, parents[end], end);
	e->flow += volume;
	e->residual -= volume;
	
	e = find_edge(g, end, parents[end]);
	e->residual += volume;
	
	augment_path(g, start, parents[end], parents, volume);
}

void netflow(graph *g, int source, int sink){
	int volume;
	
	//add_residual_edges(g);
	initialize_search(g);
	bfs(g, source);
	
	
	volume = path_volume(g, source, sink, parent);
	
	while(volume > 0){
		augment_path(g, source, sink, parent, volume);
		initialize_search(g);
		bfs(g, source);
		volume = path_volume(g, source, sink, parent);
	}
	
}

int main(void){
	
	int i;
	graph g;
	bool directed = false; //i want to add returning leg automatically and assign it a capacity of 0;
	
	read_graph(&g, directed);
	print_graph(&g);
	netflow(&g, 1, 7);
	printf("--------------\n");
	print_graph(&g);

// first row #V #END// then next rows are #V1 #V2 weight
//larger one from Skiena p.219
/*
7 10
1 2 5
1 5 12
2 4 9
2 3 7
3 4 3
3 7 5
4 6 3
5 4 4
5 6 7
6 7 2
*/		
	
	return 0;
}