
#include <stdio.h>
#include <string.h>

/* Skiena section 2.5.3, page 44

Problem: Substring Pattern Matching
Input: A text string t and a pattern string p.
Output: Does t contain the pattern p as a substring, and if so where?

*/

// look for pattern p in string t
int findmatch(char *p, char *t){
	int i, j; 				// counters
	int m, n; 				// lengths of strings p and tan
	
	m = strlen(t);
	n = strlen(p);
	
	for (i = 0; i <= (m-n); i++){
		j = 0;
		while ((j<n) && (p[j] == t[i+j]))
			j++;
		if (j == n)
			return i;
	}
	return -1;
}

int main(void){
	
	char pattern[] = "out";
	char str[] = "I am on the lookout for something!";
	
	printf("result = %d\n", findmatch(pattern, str));
	
	return 0;
}