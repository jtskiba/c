/*
K&R Ch5, ex5-5 Pointers, p.89
Write versions of the library functions strncpy, strncat, and strncmp, which
operate on at most the first n characters of their argument strings. For example,
strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in Appendix B.

// done for the last one - strncmp

*/

#include <stdio.h>
#include <string.h>

#define MAX_STRING_LEN 100

void strcat_ch2(char s[], char t[]);
void strcat_exer(char *s, char *t);
int strend(char *s, char *t);
int kr_strcmp(char *s, char *t);

void my_strncpy(char *s,char *t, int n);
void my_strncat(char s[], char t[], int n);
int kr_strncmp(char *s, char *t, int n);

int main(void)
{	
	char S1[MAX_STRING_LEN];
	char S2[MAX_STRING_LEN];
	int out;
  
	printf("String1:\t");
	scanf("%s",S1);

	printf("String2:\t");
	scanf("%s",S2);
	
	//my_strncat(S1, S2, 3);
	out = kr_strncmp(S1, S2, 4);
	
	printf("Out:\t\t%d\n", out);
	
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

/* strncat: char *strncat(char *dest, const char *src, size_t n) 
appends the string pointed to by src to the end of the string 
pointed to by dest up to n characters long.*/
void my_strncat(char s[], char t[], int n)
{
	int i, j;
	i = j = 0;
	while (s[i] != '\0') /* find end of s */
		i++;
	while (((s[i++] = t[j++]) != '\0') && j < n){
		;			
	s[i] = '\0';
	}	
}

/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int kr_strcmp(char *s, char *t)
{
	for ( ; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}

/* The C library function 
int strncmp(const char *str1, const char *str2, size_t n) 
compares at most the first n bytes of str1 and str2.
*/
int kr_strncmp(char *s, char *t, int n)
{
	int i = 0;
	for ( ; (*s == *t) && (i < n); s++, t++, i++)
		if ((*s == *t) && ((i+1) == n))
			return 0;
		else if (*s == '\0')
			return 0;
	return *s - *t;
}

