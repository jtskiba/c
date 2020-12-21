#include <stdio.h>
#include <string.h>

#define MATCH 0
#define INSERT 1
#define DELETE 2


/* Skiena section 8.2 Dynamic programming - Approximate String Matching
*/

int indel(char s){
	return(1);
}

int match(char a, char b){
	if (a == b) return(0);
	else return(1);
}

// recursive exhaustive search
int string_compare_r(char *s, char *t, int i, int j){
	int k;
	int opt[3];
	int lowest_cost;
	
	if (i == 0) return(j * indel(' '));
	if (j == 0) return(i * indel(' '));
	
	opt[MATCH] = string_compare_r(s,t,i-1,j-1) + match(s[i],t[j]);
	opt[INSERT] = string_compare_r(s,t,i,j-1) + indel(t[j]);
	opt[DELETE] = string_compare_r(s,t,i-1,j) + indel(s[i]);
	
	lowest_cost = opt[MATCH];
	for (k=INSERT; k<=DELETE;k++)
		if (lowest_cost > opt[k])
			lowest_cost = opt[k];
		
	return(lowest_cost);
}



int main(void){
	char *text = "Thou shalt no";
	char *pattern = "You should no";
	printf("cost=%d\n",string_compare_r(text, pattern, 13, 13));    // slooooow takes about 20 seconds on Lenovo X1 Yoga
	
}
