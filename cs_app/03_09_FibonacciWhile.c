#include <stdio.h>
#include <stdlib.h>

//p.259 PP3.27

// Write goto code for a function called fibonacci to print fibonacci numbers using
// a while loop. Apply the guarded-do transformation.

int fib_while(int n){
// assumes n>=3	
	int i=3;
	int two_back = 0, one_back = 1;
	int sum;
	
	while (i<=n){
		sum = one_back + two_back;
		two_back = one_back;
		one_back = sum;
		i++;
	}
	return sum;
}

int fib_while_jump2middle(int n){
// assumes n>=3
	int i=3;
	int two_back = 0, one_back = 1;
	int sum;
	int condition;
	
	goto test;
	
	loop:
		sum = one_back + two_back;
		two_back = one_back;
		one_back = sum;
		i++;
	test:
		condition = (i<=n);
		if (condition)
			goto loop;
		return sum;
}

int fib_while_guarded_do(int n){
// assumes n>=3
	int i=3;
	int two_back = 0, one_back = 1;
	int sum;
	int condition;
	
	condition = (i<=n);
	if (!condition)
		goto done;

	loop:
		sum = one_back + two_back;
		two_back = one_back;
		one_back = sum;
		i++;
		condition = (i<=n);
		if (condition)
			goto loop;
	done:
		return sum;
}


int main(void){
	int k = 6; 
	printf("fib(%d)=%d\n", k, fib_while(k));
	printf("fib_j2m(%d)=%d\n", k, fib_while_jump2middle(k));
	printf("fib_guarded(%d)=%d\n", k, fib_while_guarded_do(k));
}