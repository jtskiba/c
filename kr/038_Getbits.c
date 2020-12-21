/*
K&R 2.7 p45

getbits(x,p,n) returns the (right adjusted) n-bit field of x that 
begins at position p. We assume that bit position 0 is at the right 
end and that n and p are sensible positive values. For example,
getbits(x,4,3) returns the three bits in positions 4, 3 and 2, 
right-adjusted.
*/

#include<stdio.h>
#include<limits.h>

unsigned getbits(unsigned x, int p, int n)

int main(void)
{        
	char s1[100];
	char s2[100];

	printf("Type s1:\n");
	gets(s1);
	printf("\nType s2:\n");
	gets(s2);
	
	printf("%d\n", any(s1,s2));
 
    return 0;
}

/* getbits: get n bits from position p */

unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}

