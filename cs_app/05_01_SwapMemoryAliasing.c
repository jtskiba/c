#include <stdio.h>

/* Swap value x at xp with value y at yp */
void swap(long *xp, long *yp)
{
	*xp = *xp + *yp; /* x+y */
	*yp = *xp - *yp; /* x+y-y = x */
	*xp = *xp - *yp; /* x+y-x = y */
}


int main(void){
	
	// Loading swap with different values
	long x = 1;
	long y = 2;
	
	swap(&x, &y);
	printf("x=%d, y=%d\n", x, y);
	
	// Loading swap with same values
	x = 2;
	y = 2;
	swap(&x, &y);
	printf("x=%d, y=%d\n", x, y);
	
	
	// Loading swap with same pointers
	x = 3;
	swap(&x, &x);
	printf("x=%d\n", x);
}

//528
