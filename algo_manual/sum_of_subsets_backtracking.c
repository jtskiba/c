#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Backtracking - Sum of Subsets, given a set of numbers, pick those whose sum will equal to a specified target

#define NMAX 100

bool finished = false;  //to finish routine at request (here to stop printing when first solution to sudoku is found)
int set[] = {5, 10, 12, 13, 15, 18};

void make_move(int a[], int k, int n){
	// not required 
}

void unmake_move(int a[], int k, int n){
	// not required 
}

bool is_a_solution(int a[], int k, int target){
	int i;
	int sum = 0;
	for (i=1;i<=k;i++)
		sum = sum + a[i];
	return (sum == target);
}

void process_solution(int a[], int k){
	int i;
	printf("( ");
	for (i=1; i<=k; i++)
		printf("%d ", a[i]);
	printf(")\n");
}

void construct_candidates(int a[], int k, int target, int c[], int *ncandidates){
	int i, j;
	bool in_subset[NMAX]; // who is the permutation
	int size = sizeof(set)/sizeof(int);
	int sum = 0;
	
	// partial sum of the solution so far - for pruning
	for (i=1;i<k;i++){
		sum+=a[i];
	}
	
	for (i=1;i<NMAX;i++)
		in_subset[i] = false;
	for (i=1;i<k;i++)
		for (j=1; j<=size; j++) //MAKE MORE GENERIC
			if (a[i] == set[j-1])
				in_subset[j] = true;
	
	*ncandidates = 0;
	for(i=1; i<=size; i++){
		if ((in_subset[i] == false) && ((sum+set[i-1])<=target)){ //latter condition for pruning, your candidate when added to current sum can't exceed the target
			c[*ncandidates] = set[i-1];
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
		//printf("k=%d\n",k);
		
		construct_candidates(a, k, n, c, &ncandidates);
		/*
		for (i=0; i<ncandidates;i++)
			printf("%d ",c[i]);
		printf("\n");
		*/
		for (i=0; i<ncandidates; i++){
			a[k] = c[i];
			//printf("a[%d]=%d\n", k, c[i]);
			make_move(a, k, n);
			backtrack(a, k, n);
			unmake_move(a, k, n);
			if (finished) return;  // terminate early
		}
	}
}

void generate_subsets(int target){
	//set is defined outside main as a global array
	int a[NMAX];
	int start = 0;
	backtrack(a, start, target);
}


int main(void){
	
	generate_subsets(30);
	
	return 0;
}