#include <stdio.h>

void inplace_swap(int *x, int *y){
	*y = *x ^ *y;
	*x = *x ^ *y;
	*y = *x ^ *y;
}

void reverse_array(int a[], int cnt){
	int first, last;
	for (first = 0, last = cnt-1;
		 first<=last;    /// this needs to be modified to "<" in order to remove the bug from the below when odd number of elements in the array
		 first++,last--){
			 inplace_swap(&a[first],&a[last]);
		 }
}

void print_array(int a[], int cnt){
	int i;
	for (i=0;i<cnt;i++)
		printf("%d ",a[i]);
	printf("\n");
}

int main(void){
	
		
	//////////////////////////////////////////////////////////
	//// Chapter 2 Representing and Manipulating Information 
	//////////////////////////////////////////////////////////
	
	//p.52 PP2.11
	int a[5] = {1, 2, 3, 4, 5}; 
	print_array(a,5);
	reverse_array(a, 5);
	print_array(a,5);
	
	
	
	
	return 0;
}