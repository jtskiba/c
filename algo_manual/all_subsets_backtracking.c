#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Skiena section 7.1.1 Backtracaking - All Subsets, page 233

#define NMAX 100

bool finished = false;  //to finish routine at request (here to stop printing when first solution to sudoku is found)

void make_move(int a[], int k, int n){
	// not required 
}

void unmake_move(int a[], int k, int n){
	// not required 
}

bool is_a_solution(int a[], int k, int n){
	return (k == n);
}

void process_solution(int a[], int k){
	int i;
	
	printf("{ ");
	for (i=1; i<=k; i++){
		if (a[i]==true)
			printf("%d ", i);
	}
	printf("}\n");
}


void construct_candidates(int a[], int k, int n, int c[], int *ncandidates){
	c[0] = true;
	c[1] = false;
	*ncandidates = 2;
}	


void backtrack(int a[], int k, int n){
	int c[NMAX]; //candidates for next position
	int ncandidates; // next position candidate count
	int i; //counter
	
	
	if (is_a_solution(a, k, n)){
		process_solution(a, k);
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


void generate_subsets(int n){
	int a[NMAX];
	int start = 0;
	backtrack(a, start, n);
}


int main(void){
	
	generate_subsets(4);
	
	
	return 0;
}