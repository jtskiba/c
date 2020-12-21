#include <stdio.h>
#include <stdlib.h>


void swap(int *, int *);
void insertion_sort(int s[], int n);

int main(void){
	
	int i, j; /*for iterations*/ 
	int n=10; /*array length*/
	int s[n]; /*array*/
	
	for (i=0; i<n; ++i) /*generate an array of n random numbers*/
		s[i]=rand(); /*random int generator from <stdlib.h> */
	
	for (i=0; i< n; ++i) /*print unsorted array elements*/
		printf("%d\n",s[i]);
	printf("\n");
	
	
	insertion_sort(s, n); /* performance is n^2 */

		
	for (i = 0; i < n; ++i) /*print sorted array elements*/
		printf("%d\n",s[i]);
	
	return 0;
}

void swap(int *px, int *py){ /*interchange *px and *py - see K&R*/
	int temp;
	temp = *px;
	*px = *py;
	*py = temp;	
}

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





