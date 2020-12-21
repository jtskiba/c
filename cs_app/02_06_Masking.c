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
	int hx = 0x89ABCDEF;
	printf("%x & 0xFF = %x\n", hx, hx&0xFF); //0xFF is 0000001111 (or 255 in dec) so will be pulling 1 least significant byte
	printf("%x & ~0 (i.e. mask of all 1's) = %x\n\n", hx, hx&(~0));
	
	// PP2.12 p.53
	int x = 0x87654321;
	printf("x=%x\n", x);
	printf("a) least signif byte of x = %x\n", x&0xFF);
	printf("b) All but the least significant byte of x complemented, with the least significant byte left unchanged. \n x = %x\n", (~x&(~0xFF))|(x&0xFF));
	printf("c) The least significant byte set to all 1s, and all other bytes of x left unchanged.\n x = %x\n",(x&(~0xFF))|((~0)&0xFF));
	
	return 0;
}