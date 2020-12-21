#include <stdio.h>

void inplace_swap(int *x, int *y){
	*y = *x ^ *y;
	*x = *x ^ *y;
	*y = *x ^ *y;
}


int main(void){
	
		
	//////////////////////////////////////////////////////////
	//// Chapter 2 Representing and Manipulating Information 
	//////////////////////////////////////////////////////////
	
	//p.42 PP2.10
	int a = 1, b = 2;
	printf("a=%d, b=%d\n",a,b);
	inplace_swap(&a, &b);
	printf("a=%d, b=%d\n",a,b);
	
	
	
	return 0;
}