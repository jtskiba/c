/*
K&R ex3.3 p.53

Write a function expand(s1,s2) that expands shorthand notations 
like a-z in the string s1 into the equivalent complete list abc...xyz 
in s2. Allow for letters of either case and digits, and be prepared to 
handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a
leading or trailing - is taken literally
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

void expand(char s2[], char s1[]);

int main(void)
{       	
	char str1[100];
	char str2[100];
	
	printf("Enter before-expansion string:\n");
	gets(str1);
	
	expand(str2, str1);
	printf("%s", str2);
		
	return 0;
}

void expand(char s2[], char s1[])
{
	int i, j, k;
	for (i = j = 0; s1[i] != '\0'; i++){
		if (s1[i] != '-')
			s2[j++] = s1[i];
		else
			for (k = ((int)s1[i-1] + 1); k <= ((int)s1[i+1] - 1); k++)
				s2[j++] = (char)(k);
	}
	s2[j] = '\0';
}
