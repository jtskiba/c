
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // needed for INT_MIN
#include <stdbool.h> //need this to recognise bool type, otherwise it is _Bool

/* Skiena Chapter 6 - Weighted graphs, 3 algos are covered:
- 6.1 Minimum spanning tree (prim's algo, kruskal's algo, union-find data structure)
- 6.3 Shortest Paths (Dijkstra's algo, Floyd's all-pairs shortest path)
- 6.5 Maximum flow (i.e. Network flows and bipartite matching)
*/

//// PRIM'S ALGO


// below is the graph representation adjacency list, with some BFS specific updates

#define MAXV 1000 //max no of vertices


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

void find_path(int start, int end, int parents[]){
	if ((start==end) || (end==-1))
		printf("\n%d", start);
	else {
		find_path(start, parents[end],parents);
		printf("\n%d",end);
	}
}


// below adding BFS/DFS ones: - seen globally, hence outside main
bool processed[MAXV+1];  //which vertices have been processed, i.e. all routes from it examined
bool discovered[MAXV+1]; //which vertices have been found/discovered, i.e. not all routes from it examined yet
int parent[MAXV+1];   //discovery relation // for depth first recursive 

int dijkstra(graph *g, int start, int end){  
	int i;                // counter
	edgenode *p;          // temp pointer
	bool intree[MAXV+1]; // is the vertex in the tree yet?
	int distance[MAXV+1]; //cost of adding to tree
	int v; // current vertex to processed
	int w; // candidate vertex to process
	int weight;  // edge weight
	int dist;	 // best current distance from start
	
	//initialisation:
	for (i=1; i<=g->nvertices; i++){
		intree[i] = false;
		distance[i] = INT_MAX;
		parent[i] = -1;
	}
	v = start;
	distance[v] = 0;
	
	while(intree[v] == false){
		//edge_drawn = 0;
		intree[v] = true;
		p = g->edges[v];
		while (p != NULL){
			w = p->y;
			weight = p->weight;
			if (distance[w] > (distance[v] + weight)){
				distance[w] = distance[v] + weight;
				parent[w] = v;
			}
			p = p->next;
		}
		//v = 1; 
		dist = INT_MAX;
		for (i=1; i<=g->nvertices; i++){
			if ((intree[i] == false) && (distance[i] < dist)){
				dist = distance[i];
				v = i;
		
			}
		}
	}	
	find_path(start, end, parent);
	return(distance[end]); // reporting final distance of the minimum spanning tree
}


int main(void){
	
	int i;
	graph g;
	bool directed = false;
	
	
	read_graph(&g, directed);
	print_graph(&g);
	
	printf("Dijkstra's algo - path is:");
	i = dijkstra(&g, 1, 5); 
	printf("\nLength of the path is: %d", i);
	
	
// baby example - taken from Skiena p.196 where A=1, B=2, C=3, D=4, E=5, F=6, G=7
// first row #V #END// then next rows are #V1 #V2 weight
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