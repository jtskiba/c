/*
K&R ex3.6 p.53

Write a version of itoa that accepts three arguments instead of two. 
The third argument is a minimum field width; the converted number 
must be padded with blanks on the left if necessary to make it wide enough.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

void reverse(char s[]);
void js_itoa(int n, char s[]);
void kr_itoa(int n, char s[]);
void padded_itoa(int n, char s[], int width);

int main(void)
{       	
	char str1[100];
	char str2[100];
	int number, min_width;
	//int number = INT_MIN;
	//printf("INT_MIN is: %d\n", number);
	printf("Enter number to convert to string:\n");
	scanf("%d", &number);
    printf("Enter min width to pad with 0s:\n");
	scanf("%d", &min_width);
	

	js_itoa(number, str1);
	padded_itoa(number, str2, min_width);
	printf("Its string version is (before): %s\n",str1);		
	printf("Its string version is (padded): %s\n",str2);	
	return 0;
}


/* itoa: convert n to characters in s */
void padded_itoa(int n, char s[], int width)
{
	int i, sign, flag;
	if (n == INT_MIN)
		flag = 1;
	else
		flag = 0;
	
	if (flag == 0){
		if ((sign = n) < 0) /* record sign */
			n = -n; /* make n positive */
	}
	else
		n = INT_MAX;
			
	i = 0;
	do { /* generate digits in reverse order */
		if (flag = 1 && i == 0)
			s[i++] = ((n % 10) + 1) + '0';
		else
			s[i++] = (n % 10) + '0'; /* get next digit */
	} while ((n /= 10) > 0); /* delete it */
	if (sign < 0)
		s[i++] = '-';
	while (i < width)
	    s[i++] = 'B'; /* this is my code for 'blank' */
	s[i] = '\0';
	reverse(s);
}

/* itoa: convert n to characters in s */
void js_itoa(int n, char s[])
{
	int i, sign, flag;
	if (n == INT_MIN)
		flag = 1;
	else
		flag = 0;
	
	if (flag == 0){
		if ((sign = n) < 0) /* record sign */
			n = -n; /* make n positive */
	}
	else
		n = INT_MAX;
			
	i = 0;
	do { /* generate digits in reverse order */
		if (flag = 1 && i == 0)
			s[i++] = ((n % 10) + 1) + '0';
		else
			s[i++] = (n % 10) + '0'; /* get next digit */
	} while ((n /= 10) > 0); /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void kr_itoa(int n, char s[])
{
	int i, sign;
	
	if ((sign = n) < 0) /* record sign */
		n = -n; /* make n positive */
	i = 0;
	do { /* generate digits in reverse order */
		s[i++] = (n % 10) + '0'; /* get next digit */
	} while ((n /= 10) > 0); /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* reverse: reverse string s in place */
void reverse(char s[])
{
	int c, i, j;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
