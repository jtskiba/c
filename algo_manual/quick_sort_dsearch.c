#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *, int *);
void quick_sort_rand(int s[], int left, int right); //this is done in O(nlogn) time
int quick_sort_rsearch(int s[], int left, int right, int index_wanted);  //this is search that does not need full sorting, hence can reduce time to O(n) on av
int quick_sort_dsearch(int s[], int left, int right, int index_wanted); //same as rsearch, just not using rand and still getting O(n) but always, not on av
void insertion_sort(int s[], int n);
int choose_pivot(int s[], int left, int n);

int main(void){
	
	int i, j; /*for iterations*/ 
	int n=10; /*array length*/
	int s[n]; /*array*/
	//int try[35] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 10, 11, 12, 13, 14, 11, 11, 11, 11, 11, 10, 11, 13, 13, 13, 10, 10, 10, 13, 14};
	//int try[5] = {0, 40, 33, 10, 20};
	
	srand((unsigned int)time(NULL)); //improvement to below rand, i.e. srand sets a seed as input, and time changes every second
	for (i=0; i<n; ++i) /*generate an array of n random numbers*/{
		s[i]=rand(); /*random int generator from <stdlib.h> */
	}
	
	for (i=0; i< n; ++i) /*print unsorted array elements*/
		printf("%d\n",s[i]);
	printf("\n");
	
	
	//quick_sort_rand(s, 0, n-1); /* performance is n^2 */
	
	//for (i = 0; i < n; ++i) /*print sorted array elements*/
	//	printf("%d\n",s[i]);
	
	printf("\nout = %d\n", quick_sort_dsearch(s, 0, n-1, 0)); // picks the smallest element, ie index=0 (last col)
	
	//printf("median=%d\n", choose_pivot(try, 0, 5));
	
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

// picks the ith smallest element from the sorted array (does not do full sorting, just necessary ones to get to seought item
// smallest item is when index_wanted=0
int quick_sort_rsearch(int s[], int left, int right, int index_wanted){
	int i, last, r;
	void swap(int *px, int *py);
	
	if (left >= right) // do nothing if array contains fewer than 2 elts
		return s[index_wanted];
	
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
	if (last == index_wanted){
		//printf("M:last=%d\n",last);
		return s[last];
		}
	else {
		if (last > index_wanted){
			//printf("L:left=%d, right=%d, index=%d\n",left, last-1, index_wanted);
			quick_sort_rsearch(s, left, last-1, index_wanted);
		}
		else{
			//printf("R:left=%d, right=%d, index=%d\n",last+1, right, index_wanted);
			quick_sort_rsearch(s, last+1, right, index_wanted);
		}
	}
}

// picks the ith smallest element from the sorted array (does not do full sorting, just necessary ones to get to seought item
// smallest item is when index_wanted=0, here no randomisation, it is deterministic and always gets O(n) performance
int quick_sort_dsearch(int s[], int left, int right, int index_wanted){
	int i, last, r;
	void swap(int *px, int *py);
	
	if (left >= right) // do nothing if array contains fewer than 2 elts
		return s[index_wanted];
	
	//pick one of the below
	//r = (left+right)/2; // used in K&R - picks middle elt
	//r = left + (rand() % (right-left+1)); //not exactly uniform random (as rand() returns values from 0 to RAND_MAX of 
	        // above r picks number from left to right, inclusive
	//printf("---%d\n",r);
	r = choose_pivot(s, left, right-left+1);
	printf(">index=%d\n",r);
	
	swap(&s[left], &s[r]); // move partition elt to s[0]
	last = left;
	for (i=left+1;i<=right; i++){ // partition
		if (s[i] < s[left])
			swap(&s[++last], &s[i]);
	}
	swap(&s[left], &s[last]); //restore partition elt
	if (last == index_wanted){
		//printf("M:last=%d\n",last);
		return s[last];
		}
	else {
		if (last > index_wanted){
			//printf("L:left=%d, right=%d, index=%d\n",left, last-1, index_wanted);
			quick_sort_rsearch(s, left, last-1, index_wanted);
		}
		else{
			//printf("R:left=%d, right=%d, index=%d\n",last+1, right, index_wanted);
			quick_sort_rsearch(s, last+1, right, index_wanted);
		}
	}
}


// for sorting small arrays of 5 elements only, Tim Roughgarden using mergesort - I could but my implementation is queue driven and takes lots of code lines
// so preferred to just pick this one instead of mergesort
void insertion_sort(int s[], int n){
	int i, j;		
	for (i=1; i<n; i++){ /* insertion sort */
		j=i;
		while ((j>0) && (s[j] < s[j-1])){
			swap(&s[j],&s[j-1]);
			j--;
		}
	}	
}

int choose_pivot(int s[], int left, int n){
	int i, j, m; 
	int segment[5];
	m = 0;
	//if ((n % 5) == 0){
	int medians[n/5 + 1];
	//}
	//else{
	//	int medians[(n/5)+1];
	//}
	
	for(i=0;i<n;i++){
		j = i%5;
		segment[j] = s[left+i];
		if (j==4){
			insertion_sort(segment, 5);
			medians[m++] = segment[2]; // pick median of this segment of 5 elts, i.e. item index 2
			//printf("->%d\n", medians[m-1]);
		}
	}
	if ((j % 5) != 0){
		insertion_sort(segment, j+1);
		medians[m] = segment[(j+1)/2];
		//printf(">>%d\n", medians[m]);
	}
	if (m < 5){
		insertion_sort(medians, m+1);
		printf(">median=%d\n",medians[m/2]);
		for (i=left; i < n; i++){
			if (s[i] == medians[m/2])
				return i;
			}
		//return medians[m/2];
	}
	else{
		//printf("->m+1=%d\n", m+1);
		choose_pivot(medians, left, m+1);
	}
			
}

