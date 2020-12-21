#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *, int *);
void quick_sort_rand(int s[], int left, int right);

int main(void){
	
	int i, j; /*for iterations*/ 
	int n=10; /*array length*/
	int s[n]; /*array*/
	
	srand((unsigned int)time(NULL)); //improvement to below rand, i.e. srand sets a seed as input, and time changes every second
	for (i=0; i<n; ++i) /*generate an array of n random numbers*/{
		s[i]=rand(); /*random int generator from <stdlib.h> */
	}
	
	for (i=0; i< n; ++i) /*print unsorted array elements*/
		printf("%d\n",s[i]);
	printf("\n");
	
	
	quick_sort_rand(s, 0, n-1); /* performance is n^2 */

		
	for (i = 0; i < n; ++i) /*print sorted array elements*/
		printf("%d\n",s[i]);
	
	return 0;
}

void swap(int *px, int *py){ /*interchange *px and *py - see K&R*/
/*alternative in K&R on page 88 */
	int temp;
	temp = *px;
	*px = *py;
	*py = temp;	
}

void quick_sort_rand(int s[], int left, int right){ //see K&R page 87
	int i, last, r;
	void swap(int *px, int *py);
	
	if (left >= right) // do nothing if array contains fewer than 2 elts
		return;
	
	//pick one of the below
	//r = (left+right)/2; // used in K&R - picks middle elt
	r = left + (rand() % (right-left+1)); //not exactly uniform random (as rand() returns values from 0 to RAND_MAX of 
	        // above r picks number from left to right, inclusive
	//printf("---%d\n",r);
	
	swap(&s[left], &s[r]); // move partition elt to s[0]
	last = left;
	for (i=left+1;i<=right; i++){ // partition
		if (s[i] < s[left])
			swap(&s[++last], &s[i]);
	}
	swap(&s[left], &s[last]); //restore partition elt
	quick_sort_rand(s, left, last-1);
	quick_sort_rand(s, last+1, right);
}


