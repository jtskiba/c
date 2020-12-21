#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Skiena section 7.1.1 Backtracaking - All Partitions, page 234

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
	printf("( ");
	for (i=1; i<=k; i++)
		printf("%d ", a[i]);
	printf(")\n");
}

void construct_candidates(int a[], int k, int n, int c[], int *ncandidates){
	int i;
	bool in_perm[NMAX]; // who is the permutation
	
	for (i=1;i<NMAX;i++)
		in_perm[i] = false;
	for (i=1;i<k;i++)
		in_perm[ a[i] ] = true;
	
	*ncandidates = 0;
	for(i=1; i<=n; i++){
		if (in_perm[i] == false){
			c[*ncandidates] = i;
			*ncandidates = *ncandidates + 1;
		}
	}
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

void generate_permutations(int n){
	int a[NMAX];
	int start = 0;
	backtrack(a, start, n);
}


int main(void){
	
	generate_permutations(4);
		
	return 0;
}