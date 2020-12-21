/*
K&R ex2.5, p.45 

Write the function any(s1,s2), which returns the first location in 
a string s1 where any character from the string s2 occurs, or -1 
if s1 contains no characters from s2.
(The standard library function strpbrk does the same job but 
returns a pointer to the location.)
*/

#include<stdio.h>
#include<limits.h>

int any(char s1[], char s2[]);

int main(void)
{        
	char s1[100];
	char s2[100];

	printf("Type s1:\n");
	gets(s1);
	printf("\nType s2:\n");
	gets(s2);
	
	printf("%d\n", any(s1,s2));
 
    return 0;
}

int any(char s1[], char s2[])
{
	int i, j, c, lowest;
	
	lowest = INT_MAX;
	
	for (i = j = 0; s1[i] != '\0'; i++){
		while ((c = s2[j++]) != '\0')
			if ((s1[i] == c) && (lowest > i))
				lowest = i;
		j = 0;
	}
	if (lowest < INT_MAX)
		return lowest;
	else
		return -1;
}
