
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // needed for INT_MIN
#include <stdbool.h> //need this to recognise bool type, otherwise it is _Bool

/* Skiena Chapter 6 - Weighted graphs, 3 algos are covered:
- 6.1 Minimum spanning tree (prim's algo, kruskal's algo, union-find data structure)
- 6.3 Shortest Paths (Dijkstra's algo, floyd's all-pairs shortest path) 
- 6.5 Maximum flow (i.e. Network flows and bipartite matching)
*/

//// FLOYD MST - using adjacency matrix


// below is the graph representation adjacency list, with some BFS specific updates

#define MAXV 100 //max no of vertices


typedef struct adjacency_matrix {
	int weight[MAXV+1][MAXV+1]; // weights of nodes/vertices
	int nvertices; //no of vertices in the graph
} adjacency_matrix;



void initialize_adj_matrix(adjacency_matrix *g){
	int i, j;
	g->nvertices = 0;
	for (i=1;i<=MAXV;i++){
		for (i=1;i<=MAXV;i++){ 
			g->weight[i][j] = INT_MAX;
		}
	}
}

void read_am(adjacency_matrix *am){
	int i, j; //counter
	int nvertices, weight;
	
	initialize_adj_matrix(am);
		
	scanf("%d", &nvertices);
	am->nvertices = nvertices;
	//printf("nv=%d, %d\n",am->nvertices, nvertices);
	
	for (i=1; i<=(am->nvertices); i++){
		for (j=1; j<=(am->nvertices); j++){
			scanf("%d", &weight);
			if (weight == 0) //no edge between i and j
				am->weight[i][j] = INT_MAX;
			else
				am->weight[i][j] = weight;			
				
		}
	}
	
}

void print_am(adjacency_matrix *am){
	int i, j;
	
	
	for (i=1; i<=(am->nvertices); i++){
		for (j=1; j<=(am->nvertices); j++){
			if (am->weight[i][j] == INT_MAX)  // no edge between i and j
				printf("%2d ", 0);
			else
				printf("%2d ", am->weight[i][j]);
		}
		printf("\n");
	}
}
// END GRAPH tools

void floyd(adjacency_matrix *g){
	int i, j, k;
	int through_k;
		
	for (k=1; k<=(g->nvertices); k++){
		for (i=1; i<=(g->nvertices); i++){
			for (j=1; j<=(g->nvertices); j++){
				if ((g->weight[i][k] != INT_MAX) && (g->weight[k][j] != INT_MAX)) {  //weight[i][j] = INT_MAX when there is no path between i and j
					through_k = g->weight[i][k] + g->weight[k][j];
					if (g->weight[i][j] > through_k)
						g->weight[i][j] = through_k;
				}
			}
		}
	}
}


int main(void){
	
	int i;
	adjacency_matrix g;
	
	read_am(&g);
	//print_am(&g);
	printf("-----------------------\n");	
	floyd(&g); 
	print_am(&g);
	
	
// baby example - taken from Skiena p.196 where A=1, B=2, C=3, D=4, E=5, F=6, G=7 (this time presented as adjacency matrix)
// first row #V, then
// matrix, note that 0s are no-edges (get converted internally to INT_MAX and when printed INT_MAX becomes 0 again)
/*
7
 0  5  0  7 12  0  0
 5  0  7  9  0  0  0
 0  7  0  4  0  2  5
 7  9  4  0  4  3  0
12  0  0  4  0  7  0
 0  0  2  3  7  0  2
 0  0  5  0  0  2  0
*/

	
	return 0;
}