#include <stdio.h>
#include <float.h>
#include <limits.h>

// single precision Sign:1, Exponent:8 , Fractions:23, Total:32bits
// double precision Sign:1, Exponent:11, Fractions:52, Total:64bits

// below are for double
#define POS_INFINITY 0x7FF0000000000000 //(0x7FF<<52)   //0 111 1111 1111 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 
#define NEG_INFINITY 0xFFF0000000000000 //(0xFFF<<52)   //1 111 1111 1111 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 
#define NEG_ZERO 	 0x8000000000000000 //(0x8<<63)     //1 000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 

/* Solutions: (the above works fine too)
#define POS_INFINITY 1e400   //this is because max double precision is 1.8 × 10^308 and beyond that should overflow to Inf 
#define NEG_INFINITY (-POS_INFINITY)
#define NEG_ZERO (-1.0/POS_INFINITY)
*/

int main(void){
			
	/*		
	//////////////////////////////////////////////////////////
	//// Chapter 2 Representing and Manipulating Information 
	//////////////////////////////////////////////////////////
	*/
	
	//PP2.53 p.115
	printf("double +inf = %f\n", POS_INFINITY);
	printf("double -inf = %f\n", NEG_INFINITY);	
	printf("double -zer = %f\n\n", NEG_ZERO);		
	
	printf("INT_MAX = %d\n",INT_MAX);
	printf("FLT_MAX = %f\n",FLT_MAX);
	printf("INT_MAX <= FLT_MAX: %d\n",INT_MAX<=FLT_MAX);
	printf("INT_MAX == (int)(float) INT_MAX: %d\n\n", INT_MAX==(int)(float)INT_MAX);
	
	//from summary of ch2
	printf("masking: %x\n", (1<<8)); //expecting 0x100
	printf("masking: %x\n", -1); //expecting 0xFFF...F
	printf("masking: %x\n", (1<<8)-1); //expecting 0xFF
	
	return 0;
}