#include <stdio.h>
#include <string.h>
#include <limits.h>

#define M 31 //2^5-1
#define N 8 //2^3

int optarith(int x, int y){
	int t = x;
	x <<= 5;
	x -= t;
	if (y<0) y += 7;
	y >>= 3; /*arithmetic shift*/
	return x+y;
}

int arith(int x, int y){
	int result = 0;
	printf("xM=%d, y/N=%d\n",x*M,y/N);
	result = x*M + y/N;
	return result;
}

int main(void){
			
	/*		
	//////////////////////////////////////////////////////////
	//// Chapter 2 Representing and Manipulating Information 
	//////////////////////////////////////////////////////////
	*/
	int x = 6;
	int y = -17;
		
	//PP2.43 p.98
	printf("optarith x=%d, y=%d, res=%d\n", x, y, optarith(x,y));
	printf("   arith x=%d, y=%d, res=%d\n\n", x, y, arith(x,y));
	
	//PP2.44 p.99
	int z = INT_MIN;
	printf("%d\n", (-z)>=0);
	
	return 0;
}