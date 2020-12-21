
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // needed for INT_MIN
#include <stdbool.h> //need this to recognise bool type, otherwise it is _Bool

/* Skiena section 5.6, page 162

Problem: Implementation of breadth first search
includes:
- path finder 5.6.2 (p.165)
- connected components 5.7.1 (p.166)

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
	//printf("%d %d\n", (g->nvertices), m);
	
	for (i=1; i<=m; i++){
		scanf("%d %d", &x, &y);
		//printf("%d %d\n", x, y);
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


// below adding BFS ones: - seen globally, hence outside main
bool processed[MAXV+1];  //which vertices have been processed, i.e. all routes from it examined
bool discovered[MAXV+1]; //which vertices have been found/discovered, i.e. not all routes from it examined yet
int parent[MAXV+1];   //discovery relation

void initialize_search(graph *g){
	int i;
	for (i=1; i<=g->nvertices; i++){
		processed[i] = false;
		discovered[i] = false;
		parent[i] = -1;
	}
}
/*
//below 3 functions can be filled in as needed
void process_vertex_early(int v){
	printf("processed vertex %d\n", v);
}

void process_vertex_late(int v){
}

void process_edge(int x, int y){
	printf("processed edge (%d %d)\n", x, y);
	// or e.g.
	// nedges++;
}
*/
// for connected components
void process_vertex_early(int v){
	printf("%d ",v);
	// this can only bind each vertex to its component instead of printing in the connected_components routine
}

void process_edge(int x, int y){	
}

void process_vertex_late(int v){
}


// traversal below
void bfs(graph *g, int start){
		queue *q;     // queue of vertices to visit
		int v;       // current vertex that we are processing
		int y;       // successor vertex
		edgenode *p; // temp pointer
		
		q = createQueue(MAXV+1);
		enqueue(q, start);
		discovered[start] = true;
		
		while (isEmpty(q) != 1){
			v = dequeue(q);
			process_vertex_early(v);
			processed[v] = true;
			p = g->edges[v];
			while (p != NULL){
				y = p->y;
				if ((processed[y] == false) || g->directed)
					process_edge(v, y);
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

void find_path(int start, int end, int parents[]){
	if ((start==end) || (end==-1))
		printf("\n%d", start);
	else {
		find_path(start, parents[end],parents);
		printf("\n%d",end);
	}
}

// below is in relation to connected components
// degrees of separation, solving rubik cube, 15puzzle from anyposition?
// to uncoomment 


void connected_components(graph *g){
	int c; //component number
	int i; //iterator
	c = 0;
	
	initialize_search(g);
	
	for (i=1; i <= g->nvertices; i++){
		if (discovered[i] ==  false){
			c = c + 1;
			printf("Component %d: ", c);
			bfs(g, i);
			printf("\n");			
		}
	}
}



int main(void){
	
	//to use here
	graph g;
	bool directed = false;
		
	read_graph(&g, directed);
	print_graph(&g);
	
	//printf("\n");
	//bfs(&g, 1);
	printf("\n");
	
	connected_components(&g);
	
	/* input
6 5
1 5
5 6
2 3
3 4
4 2
	*/
	
		
	
	return 0;
}