/*
K&R ex2.8 p.45

Write a function rightrot(x,n) 
that returns the value of the integer x rotated
to the right by n positions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>

unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned invert(unsigned x, int p, int n);
unsigned rightrot(unsigned x, int n);
unsigned countBits(unsigned int number);


int main(void)
{        
	unsigned int a, b;
	
	a = 0b1011101;
	//b = 0b1100000;

	//printf("%d\n",setbits(a,4,3,b)); //expect 1100111 or 103 in dec or 67 in hex
	//printf("%d\n",invert(a,5,3)); //expect 011 inverted, so 100. This 100 is 4 in dec and also 4 in hex
	printf("%d\n",rightrot(a,2)); //rightmost 01 in 'a' to go to left most 2 bits
		// i.e. 1011101 turns to 0110111 (55 in decimal or 37 in hex)
	
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

/* e.g. 2 rightmost bits will show on the left */
unsigned rightrot(unsigned x, int n)
{
	unsigned count = countBits(x);
	//unsigned temp = x;
	return ((x & ~(~0 << n)) << (count - n)) + (x >> n);
		
}

unsigned countBits(unsigned int number) 
{       
      // log function in base 2  
      // take only integer part 
      return (int)log2(number)+1; 
} 

