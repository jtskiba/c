#include <stdio.h>
#include <stdlib.h>


void swap(int *, int *);
void insertion_sort(int s[], int n);
void selection_sort(int s[], int n);
void bubble_sort(int s[], int n);

int main(void){
	
	int i, j; /*for iterations*/ 
	int n=10; /*array length*/
	int s[n]; /*array*/
	
	for (i=0; i<n; ++i) /*generate an array of n random numbers*/
		s[i]=rand(); /*random int generator from <stdlib.h> */
	
	for (i=0; i< n; ++i) /*print unsorted array elements*/
		printf("%d\n",s[i]);
	printf("\n");
	
	
	//insertion_sort(s, n); /* performance is n^2 */
    //selection_sort(s, n); /* performance is n^2 */	
	bubble_sort(s, n); /* performance is n^2 */	

	//printf("\nsize: %d\n\n",sizeof(s)/sizeof(int)); //prints size of array i.e. 40 / 4 = 10

		
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

void selection_sort(int s[], int n){
	int i, j; //counters
	int min; //index of minimum
	for (i=0; i<n; i++){
		min=i;
		for (j=i+1;j<n;j++)
			if (s[j] < s[min]) min=j;
		swap(&s[i],&s[min]);
	}
}


void bubble_sort(int s[], int n){  // https://en.wikipedia.org/wiki/Bubble_sort
	int i, j; //counters
	for (i=n; i>0; i--){
		for (j=1;j<n;j++)
			if (s[j] < s[j-1])
				swap(&s[j],&s[j-1]);
	}
}



