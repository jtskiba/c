/*
K&R ex2.6 p.45

Write a function setbits(x,p,n,y) that returns x with the n bits 
that begin at position p set to the rightmost n bits of y, 
leaving the other bits unchanged.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);

int main(void)
{        
	unsigned int a, b;
	
	a = 0b1011101;
	b = 0b1100000;
	printf("%d",setbits(a,4,3,b)); //expect 1100111 or 103 in dec or 67 in hex
	
 
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

