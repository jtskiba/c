#include <stdio.h>

int main(void){
	
	
	
	//////////////////////////////////////////////////////////
	//// Chapter 2 Representing and Manipulating Information 
	//////////////////////////////////////////////////////////
	
	//p.31 example of floating point arithmetic going wrong
	printf("(3.14+1e20)-1e20 = %f\n",(3.14+1e20)-1e20);
	printf("3.14+(1e20-1e20) = %f\n",3.14+(1e20-1e20));
	

	
	return 0;
}