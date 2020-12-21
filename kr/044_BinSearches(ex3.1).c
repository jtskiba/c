/*
K&R ex3.1 p.52

Our binary search makes two tests inside the loop, when 
one would suffice (at the price of more tests outside.) 

Write a version with only one test inside the loop and measure
the difference in run-time.

*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>


int binsearch(int x, int v[], int n);
int newbinsearch(int x, int v[], int n);


int main(void)
{        

	clock_t start_t, end_t, total_t;
	int c = 'D';
	int i;
	int n = 100;
	int arr[n];
	int to_find = 27;
	
	for (i = 0; i < n; i++){
		arr[i] = i;
	}
	
	start_t = clock();
	printf("%d\n",binsearch(to_find, arr, n));
	end_t = clock();
	total_t =(end_t - start_t);
	printf("Binsearch time taken by CPU: %ld\n", total_t );
	
	/*
	start_t = clock();
	printf("%d\n",newbinsearch(to_find, arr, n));
	end_t = clock();
	total_t = (end_t - start_t);
	printf("New_Binsearch time taken by CPU: %ld\n", total_t );
	*/
	return 0;
}



/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
/* v is in ascending order of values */
int binsearch(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	
	while (low <= high) {
		mid = (low+high)/2;
		if (x < v[mid])
			high = mid + 1;
		else if (x > v[mid])
			low = mid + 1;
		else /* found match */
			return mid;
	}
	return -1; /* no match */
}

int newbinsearch(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	mid = (low+high)/2;
	
	while ((low <= high) && (x != v[mid])) {
		if (x < v[mid])
			high = mid + 1;
		else
			low = mid + 1;
		mid = (low+high)/2;
	}
	if (x == v[mid])
		return mid; /*match */
	else 
		return -1; /* no match */
}
