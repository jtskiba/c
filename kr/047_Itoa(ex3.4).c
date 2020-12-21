/*
K&R ex3.4 p.53

In a two's complement number representation, our version of itoa does not
handle the largest negative number, that is, 
the value of n equal to -(2^(wordsize-1)). Explain why not.

ANSWER: This is because when we flip the negative to positive, then
we don't have the equivallently large positive number, and hence we
overflow
i.e. -2147483648 does not become 2147483648 as 2147483647 is the largest
positive

Modify it to print that value correctly, regardless of the machine on 
which it runs.
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

int main(void)
{       	
	char str1[100];
	char str2[100];
	int number = INT_MIN;
	printf("INT_MIN is: %d\n", number);
	//printf("Enter number to convert to string:\n");
	//scanf("%d", &number);
	
	js_itoa(number, str1);
	kr_itoa(number, str2);
	printf("Its string version is (js): %s\n",str1);		
	printf("Its string version is (kr): %s\n",str2);	
	return 0;
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