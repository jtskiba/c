#include <stdio.h>
#include <stdlib.h>

//p.260 PP3.29

/* Example of for loop containing a continue statement */
/* Sum even numbers between 0 and 9 */


int main(void){
	long sum = 0;
	long i;
	
	for (i = 0; i < 10; i++) {
		if (i & 1)
			continue;
		sum += i;
	}
	printf("sum for = %ld\n", sum);
	
	/*
	for (i = 0; i < 10; i++) {
		if (i & 1)
			continue;
		sum += i;
	}
	printf("sum = %ld\n", sum);
	*/
	
	//same with while loop
	sum=0; 
	i=0;
	while (i<10){
		
		if (i & 1){
			i++; //without this we will get an inifinite loop as the continue will skip anything in this iteration of while loop after if conditional
			continue;
		}
		sum += i;
		i++;		
	}
	printf("sum while = %ld\n", sum);
	
	//same with while loop but now using goto instead of continue
	sum=0; 
	i=0;
	while (i<10){
		
		if (i & 1){
			goto test;
		}
		sum += i;
		
		test:
			i++;		
	}
	printf("sum goto = %ld\n", sum);

	return 0;
}
