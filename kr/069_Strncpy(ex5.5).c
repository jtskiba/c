/*
K&R Ch5, ex5-5 Pointers, p.89
Write versions of the library functions strncpy, strncat, and strncmp, which
operate on at most the first n characters of their argument strings. For example,
strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in Appendix B.

// only done for the first one, and looked up what other ones are doing.

*/

#include <stdio.h>
#include <string.h>

#define MAX_STRING_LEN 100

void strcat_ch2(char s[], char t[]);
void strcat_exer(char *s, char *t);
int strend(char *s, char *t);

void my_strncpy(char *s,char *t, int n);

int main(void)
{	
	char S1[MAX_STRING_LEN];
	char S2[MAX_STRING_LEN];
	int out;
  
	printf("String1:\t");
	scanf("%s",S1);

	printf("String2:\t");
	scanf("%s",S2);
	
	my_strncpy(S1, S2, 3);
	
	printf("Out:\t\t%s\n", S1);
	
	return 0;
}


/* strncpy(s,t,n) copies at most n characters of t to s. */
void my_strncpy(char *s,char *t, int n)
{
	int i = 0;
	
	while (i < n && i <= strlen(t)){
		*s = *t;
		i++, *t++, *s++;
	}
	//*s = '\0';
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