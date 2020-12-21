/*
K&R Ch5, ex5-4 Pointers, p.89
Write the function strend(s,t), which returns 1 if the string t occurs at the
end of the string s, and zero otherwise.

*/

#include <stdio.h>
#include <string.h>

#define MAX_STRING_LEN 100

void strcat_ch2(char s[], char t[]);
void strcat_exer(char *s, char *t);
int strend(char *s, char *t);

int main(void)
{	
	char S1[MAX_STRING_LEN];
	char S2[MAX_STRING_LEN];
	int out;
  
	printf("String1:\t");
	scanf("%s",S1);

	printf("String2:\t");
	scanf("%s",S2);
	
	out = strend(S1, S2);
	
	printf("Out:\t\t%d\n", out);
	
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

/* strend returns 1 if the string t occurs at the
end of the string s, and zero otherwise.*/
int strend(char *s, char *t)
{
	int count;
	int i = (strlen(s) - 1);
	int j = (strlen(t) - 1);
	
	s = s+i;
	t = t+j;
	//printf("last in s: %c, last in t: %c\n", *s, *t);
	count = 0;
	
	
	while (*s-- == *t--) // copy t
		count++;
	if (count == (j + 1))
		return 1;
	else
		return 0;
	
}