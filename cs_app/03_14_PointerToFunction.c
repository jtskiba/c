#include <stdio.h>
#include <stdlib.h>


/*
p.306 3.10.1 Understanding Pointers.
*/

int fun(int x, int *p){
	*p *= 2;
	x *= 2;
	return (x + *p);
}	



int main(void){
	int a = 3;
	int b = 4;
	int c = fun(a,&b);
	printf("a=%d, b=%d, c=%d\n",a, b, c);
	
	
	// POinter to a function
	int (*fp)(int, int *);
	fp=fun;
	c = fp(a,&b);
	printf("a=%d, b=%d, c=%d\n",a, b, c);
	
	
	return 0;
}
