/*
K&R ex3.1 p.52

Our binary search makes two tests inside the loop, when one would 
suffice (at the price of more tests outside.) Write a version with 
only one test inside the loop and measure
the difference in run-time.

*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>

int newlower(int c);


int main(void)
{        
	int c = 'D';
	
	printf("%c\n",newlower(c));
	return 0;
}


/* newlower: convert c to lower case; ASCII only */
int newlower(int c)
{
	return ((c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c); 
}
