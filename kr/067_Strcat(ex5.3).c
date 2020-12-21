/*
K&R Ch5, ex5-3 Pointers, p.89
Write a pointer version of the function strcat that we showed in Chapter 2:
strcat(s,t) copies the string t to the end of s.

From Ch2:
"standard function strcat(s,t), which concatenates the
string t to the end of string s. strcat assumes that there is enough space in s to hold the
combination. As we have written it, strcat returns no value; the standard library version
returns a pointer to the resulting string."

*/

#include <stdio.h>

#define MAX_STRING_LEN 100

void strcat_ch2(char s[], char t[]);
void strcat_exer(char s[], char t[]);

int main(void)
{	
	char S1[MAX_STRING_LEN];
	char S2[MAX_STRING_LEN];
  
	printf("String1:\t");
	scanf("%s",S1);

	printf("String2:\t");
	scanf("%s",S2);
	
	strcat_exer(S1, S2);
	
	printf("Together:\t%s\n", S1);
	
	return 0;
}

/* strcat: concatenate t to end of s; s must be big enough */
void strcat_ch2(char s[], char t[])
{
	int i, j;
	i = j = 0;
	while (s[i] != '\0') /* find end of s */
		i++;
	while ((s[i++] = t[j++]) != '\0') /* copy t */
		;
}

/* strcat: concatenate t to end of s; s must be big enough */
void strcat_exer(char *s, char *t)
{
	//int i, j;
	//i = j = 0;
	while (*s != '\0') /* find end of s */
		s++;
	while ((*s++ = *t++) != '\0' ) /* copy t */
		;
}