
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PQ_SIZE 100 
/* Skiena section 4.3.1, page 109

Problem: Implementation of heaps

Heaps are a simple and elegant data structure for efficiently supporting the PRIORITY QUEUE 
operations insert and extract-min. They work by maintaining a partial order
on the set of elements which is weaker than the sorted order (so it can be efficient
to maintain) yet stronger than random order (so the minimum element can be
quickly identified).

*/

typedef struct {
	int n;  			// number of items (starting from 1, empty = 0), thats index of 1st item is 1
	int q[PQ_SIZE + 1]; // body of queue
} priority_queue;

int pq_parent(int n){
	if (n==1) return(-1); //it is a root of heap, so no parent
	else return ((int)(n/2));  //floored n/2
}

int pq_young_child(int n){
	return(2 * n);//if parent is index 3 then its first child is in position index 6 (second one is position 7)
}

void pq_init(priority_queue *q){
	q->n = 0;
}

void pq_insert(priority_queue *pq, int x){
	
	if (pq->n >= PQ_SIZE)
		printf("Warning: priority queue is full, can't add the item x = %d\n", x);
	else {
		pq->n = pq->n + 1;
		pq->q[pq->n] = x;
		//bubble_up(pq, pq->n); 
	}
}

void swap(int *x, int *y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void pq_swap(priority_queue *pq, int index_1, int index_2){
	int temp;
	temp = pq->q[index_1];
	pq->q[index_1] = pq->q[index_2];
	pq->q[index_2] = temp;
}

void bubble_up(priority_queue *pq, int index){
	if (pq_parent(index) == -1) return; //at root of heap, no parent 
	
	if (pq->q[pq_parent(index)] > pq->q[index]){
		pq_swap(pq, index, pq_parent(index));
		bubble_up(pq, pq_parent(index));
	}
}

void make_heap(priority_queue *q, int s[], int n){
	int i;
	pq_init(q);
	for (i = 0; i<n; i++){
		pq_insert(q, s[i]);
	}
}

void bubble_down(priority_queue *q, int p){
	int c;
	int i;
	int min_index;
	
	c = pq_young_child(p);
	min_index = p;
	
	for (i=0; i<=1; i++){
		if ((c+i) <= q->n){
			if (q->q[min_index] > q->q[c+i]) min_index = c+i;
		}
	}
	
	if (min_index != p){
		pq_swap(q, p, min_index);
		bubble_down(q, min_index);
	}
}

int extract_min(priority_queue *q){
	int min = -1;
	
	if (q->n <= 0) printf("Warning: empty priority queue.\n");
	else {
		min = q->q[1];
		q->q[1] = q->q[q->n];
		q->n = q->n - 1;
		bubble_down(q, 1);
	}
	
	return min;
}

void heapsort(int s[], int n){
	int i;
	priority_queue temp;
	make_heap(&temp, s, n);
	
	for (i=0; i<n; i++)
		s[i] = extract_min(&temp);
}

void print_array(int s[], int n){
	int i;
	for (i=0; i<n; i++)
		printf("%d ", s[i]);
	printf("\n");
}


int main(void){
	
	int s[] = {10, 5, 3, 6, 4, 19};
	print_array(s, 6);
	heapsort(s, 6);
	print_array(s, 6);
	// first one is not sorted as our heaps is starting from index 1
	
	return 0;
}