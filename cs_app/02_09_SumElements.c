#include <stdio.h>

void print_array(int a[], int cnt){
	int i;
	for (i=0;i<cnt;i++)
		printf("%d ",a[i]);
	printf("\n");
}

float sum_elements(float a[], unsigned length){
	int i;
	float result = 0;
	printf("it is = %u\n",length-1);
	
	//for (i=0;i<=length-1;i++){ //causing an error because -1 unsigned is a big number
	for (i=0;i<length;i++){	
		result+=a[i];
	}
	return result;
}

int main(void){
			
	/*		
	//////////////////////////////////////////////////////////
	//// Chapter 2 Representing and Manipulating Information 
	//////////////////////////////////////////////////////////
	*/
	
	/*p.77 PP2.25*/
	float out;
	float array[3] = {1.0, 2.3, 4.2};
	unsigned len = 0;
	
	out = sum_elements(array, len);
	printf("out=%f\n\n",out);
	
	
	return 0;
}