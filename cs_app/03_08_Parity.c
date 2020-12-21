#include <stdio.h>
#include <stdlib.h>

//p.256 PP3.26
// This code computes the parity of argument x. That is, it returns 1 if there is
// an odd number of ones in x and 0 if there is an even number.

// i dont see this = believe it is wrong as anything & 0 is always 0?

short test_one(unsigned int x){
	short val = 1;
	while (x){
		val ^= x;
		x >>= 1;
	}
	return val & 0;
}


int main(void){
	short k = 3; //or 00..0011 - so even number of 1s so should be 0
	printf("!%d: parity: %d\n", k, test_one(k));
	k=7; //or 00000111 - so odd number of 1s so should be 1 
	printf("!%d: parity: %d\n", k, test_one(k));
}