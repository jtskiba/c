#include <stdio.h>
#include <stdlib.h>

#define TYPE int

//p.249 - now doing v3 of Computer Systems which is not on IA32 but x86-64
//PP3.21
int fact_do_goto(TYPE n){
		TYPE result = 1;
		TYPE prior_result;
		TYPE of=0;
	loop:
		prior_result = result;
		result *= n;
		if (n>1){
			of = ((result/n) != prior_result);
			if (of == 1)
				return 1;
			n--;			
			goto loop;
		}
		//printf("r/n=%d, (n-1)!=%d\n", result/n, prior_result);
		of = ((result/n) != prior_result);
		return of; //checks if overflows (1 overflow, 1 no overflow)
}

int main(void){
	TYPE k = 14;
	printf("!%d: is overflowing? %d\n",k,fact_do_goto(k));
	
}