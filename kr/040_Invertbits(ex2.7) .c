/*
K&R ex2.7 p.45

Write a function invert(x,p,n) that that returns x with the n bits that begin at 
position p inverted (i.e., 1 changedinto 0 and vice versa), leaving the others unchanged. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned invert(unsigned x, int p, int n);



int main(void)
{        
	unsigned int a, b;
	
	a = 0b1011101;
	b = 0b1100000;
	//printf("%d\n",setbits(a,4,3,b)); //expect 1100111 or 103 in dec or 67 in hex
	printf("%d\n",invert(a,5,3)); //expect 011 inverted, so 100. This 100 is 4 in dec and also 4 in hex
 
    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	//return ((y & (~0 << n)) + getbits(x, p, n));
	//or if you dont want to rely on getbits, just copy it in below:
	return ((y & (~0 << n)) + ((x >> (p+1-n)) & ~(~0 << n)));
}

/* getbits: get n bits from position p */

unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}

/* below will be unary operation on getbits and then do & to keep only last n bits*/
unsigned invert(unsigned x, int p, int n)
{
	return (~((x >> (p+1-n)) & ~(~0 << n)) & ~(~0 << n));
}


