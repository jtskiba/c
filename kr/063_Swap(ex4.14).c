/*
K&R ex4.14 Recursion, p.74
Define a macro swap(t,x,y) that interchanges two arguments of type t.
(Block structure will help.)
*/

#include <stdio.h>
#include <string.h>

#define swap(t,x,y) t temp; temp = x; x = y; y = temp;

int main(void)
{       	
	int m = 2;
	int n = 3;
	
	printf("m = %d, n = %d\n",m, n);
	swap(int,m,n)
	printf("m = %d, n = %d\n",m, n);
		
	return 0;
}

