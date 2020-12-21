#include <stdio.h>
#include <string.h>
#include <limits.h>

int xpwr2k(int x, int k){
	return (x<<k);
}

int multiply(int x, int y){
	int sum, first, i, x_if_bit1;
	for (i=0, sum=0, first=1; i<sizeof(y)*sizeof(int); i++, first<<=1){
		//x_if_bit1 = ((y&first)>0)?x:0;
		//sum += x_if_bit1<<i; // to be power 2^i
		sum += (((y&first)>0)?x:0)<<i; //welcome to cryptic C!!
	}	
	return sum;
}

int pwr2k(int k){
	return 1<<k;
}

int xdiv2k(int x, int k){
	return ((x<0 ? x+pwr2k(k)-1 : x) >> k);
}

int div16(int x){
	return (x>>4);
}

int ndiv16(int x){
	return ((x+(1<<4)-1)>>4);
}

int my_div16(int x){
	int shift = sizeof(x)*sizeof(int)-1; 
	int key = (x&(1<<shift))>>shift; // if negative, key will be 1, else 0
	//printf("neg? = %d\n",key);
	return ((x+(key<<4)-key)>>4);
}

int main(void){
			
	/*		
	//////////////////////////////////////////////////////////
	//// Chapter 2 Representing and Manipulating Information 
	//////////////////////////////////////////////////////////
	*/
	int x = 6;
	int k = 3;
	int y = 5;
	// Multiplication using shifts 
	
	printf("%d*(2^%d)=%d\n",x, k, xpwr2k(x,k));
	printf("%d*%d=%d\n",x, y, multiply(x,y));
	printf("2^%d=%d\n", k, pwr2k(k));
	printf("40/(2^3)=%d\n", xdiv2k(40,k));
	
	//PP2.42 p.97
	printf(" 65/16= %d\n", div16(65));
	printf("-65/16=%d\n", ndiv16(-65));
	printf(" 65/16= %d\n", my_div16(65));
	printf("-65/16=%d\n", my_div16(-65));
	
	
	return 0;
}