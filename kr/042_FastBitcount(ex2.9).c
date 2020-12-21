/*
K&R ex2.9 p.47

In a two's complement number system, x &= (x-1) deletes the 
rightmost 1-bit in x. Explain why. 

ANSWER: 
this is because x &= (x - 1) is x = x & (x - 1)
Now x and x-1 only differ in the last bit, when one ends with 0
the other must end with 1 and so & then causes this bit to be 0
so it is deleted
but e.g. if dec=2 so bin=10 then dec-1=1 which in bin is 1 so 01
therefore resulting x is 00

Use this observation to write a faster version of bitcount.
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
int bitcount(unsigned x);
int fastbitcount(unsigned x);


int main(void)
{        
	unsigned int a, b;
	
	a = 0b1011101;
	b = 0b1100000;

	//printf("%d\n",setbits(a,4,3,b)); //expect 1100111 or 103 in dec or 67 in hex
	//printf("%d\n",invert(a,5,3)); //expect 011 inverted, so 100. This 100 is 4 in dec and also 4 in hex
	//printf("%d\n",rightrot(a,2)); //rightmost 01 in 'a' to go to left most 2 bits
		// i.e. 1011101 turns to 0110111 (55 in decimal or 37 in hex)
	//printf("%d\n",fastbitcount(a)); //expecting this to be 5 for a
    //printf("%d\n",a &= (a-1)); // a is 93, removing last bit is 1011100 so 92
	//printf("%d\n",b &= (b-1)); // b is 96 so 1100000 
		// 95 is: 1011111 so & acting on the two is: 1000000 so 64
	printf("%d\n",fastbitcount(a)); //expecting this to be 5 for a
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
	unsigned count = bitcount(x);
	//unsigned temp = x;
	return ((x & ~(~0 << n)) << (count - n)) + (x >> n);
		
}
/* counts all bits, both 0 and 1 */
unsigned countBits(unsigned int number) 
{       
      // log function in base 2  
      // take only integer part 
      return (int)log2(number)+1; 
} 

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
	int b;
	for (b = 0; x != 0; x >>= 1)
		if (x & 01)
			b++;
	return b;
}

/* fastbitcount: count 1 bits in x 
use: x = x & (x - 1) which deletes rightmost bit*/
int fastbitcount(unsigned x)
{
	int b = 0;
	while (x != 0){
		b++;
		x &= x-1;		
	}
	return b;
}
