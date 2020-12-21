#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Skiena section 7.1.1 Backtracaking - All Subsets, page 233

#define NMAX 100
#define MAXV 100


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

bool finished = false;  //to finish routine at request (here to stop printing when first solution to sudoku is found)
int solution_count = 0; // to count number of paths to the goal
graph g;


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
	p->weight = 1;
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
	//int weight; // weight of the edge (x, y)
	
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



void make_move(int a[], int k, int n){
	// not required 
}

void unmake_move(int a[], int k, int n){
	// not required 
}

bool is_a_solution(int a[], int k, int n){
	return (a[k] == n);
}

void process_solution(int a[], int k, int t){
	solution_count++;

	int i = 1;
	printf("Path %d: ", solution_count);
	while (a[i] != t){
		printf("%d>", a[i]);
		i++;
	}
	printf("%d\n",t);
	
}

void construct_candidates(int a[], int k, int n, int c[], int *ncandidates){
	int i;
	bool in_sol[NMAX]; // what's already in the solution
	edgenode *p; // temp pointer
	int last;    // last vertex on current path
	
	for (i=1;i<NMAX;i++)
		in_sol[i] = false;
	for (i=1;i<k;i++)
		in_sol[ a[i] ] = true;
	
	if (k==1){ //always starts from vertex 1
		c[0] = 1;
		*ncandidates = 1;
	}
	else{
		*ncandidates = 0;
		last = a[k-1];
		p = g.edges[last];
		while (p != NULL){
			if (!in_sol[ p->y ]){
				c[*ncandidates] = p->y;
				*ncandidates = *ncandidates + 1;
			}
			p = p->next;
		}
	}
}	

void backtrack(int a[], int k, int n){
	int c[NMAX]; //candidates for next position
	int ncandidates; // next position candidate count
	int i; //counter
		
	if (is_a_solution(a, k, n)){
		process_solution(a, k, n);
	}
	else{
		k = k + 1;
		construct_candidates(a, k, n, c, &ncandidates);
		for (i=0; i<ncandidates; i++){
			a[k] = c[i];
			make_move(a, k, n);
			backtrack(a, k, n);
			unmake_move(a, k, n);
			if (finished) return;  // terminate early
		}
	}
}

void generate_paths(int target){
	int a[NMAX];
	int start = 0;
	backtrack(a, start, target);
}


int main(void){
	
	int i;
	bool directed = false;
	read_graph(&g, directed);
	print_graph(&g);
	generate_paths(3);
	printf("sols=%d\n",solution_count);
	
/* example from Skiena p.236
6 9
1 2
1 3
1 4
1 5
2 6
3 6
4 6
5 6
3 4

*/
	
	

	
	return 0;
}