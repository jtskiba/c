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

int bis(int x, int m){
	return (x | m);
}

int bic(int x, int m){
	return (x & (~m));
}

int bool_or(int x, int y){
	return bis(x,y);
}

int bool_xor(int x, int y){
	return bis(bic(x,y),bic(y,x));
}

int main(void){
			
	//////////////////////////////////////////////////////////
	//// Chapter 2 Representing and Manipulating Information 
	//////////////////////////////////////////////////////////
	
	//p.53 PP2.13
	int x = 0xA; //1010
	int m = 0x3; //0011
	printf("x=1010 and m=0011\n");
	printf("bool_or(x,m)  = %x (expected 1011 or hex B)\n", bool_or(x,m));
	printf("bool_xor(x,m) = %x (expected 1001 or hex 9)\n", bool_xor(x,m));
	
	
	
	return 0;
}