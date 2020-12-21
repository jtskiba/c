/*
K&R Ch4.10 Recursion, p.74

*/

#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void itoa(int n, char s[]);
void printd(int n);

int main(void)
{       	
	char str1[100];
	int number;
	
	printf("Enter number to convert to string:\n");
	scanf("%d", &number);
	//itoa(number, str1);
	//printd(number);
	//printf("Its string version is (): %s\n",str1);	
	printf("Its string version is (): ");	
	printd(number);	
	return 0;
}


/* printd: print n in decimal */
void printd(int n)
{
	if (n < 0) {
		putchar('-');
		n = -n;
	}
	if (n / 10)
		printd(n / 10);
	putchar(n % 10 + '0');
}

void itoa(int n, char s[])
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