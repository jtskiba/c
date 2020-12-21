/*
K&R ex4.12 Recursion, p.74
Adapt the ideas of printd to write a recursive version of itoa; that is, convert
an integer into a string by calling a recursive routine.
*/

#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void itoa(int n, char s[]);
void printd(int n);
void itoa_rec(int n, char s[]);
void kr_qsort(int v[], int left, int right);
void swap(int v[], int i, int j);

int i = 0;

int main(void)
{       	
	char str1[100];
	int number = 234;
	itoa_rec(number, str1);
	printf("%s\n",str1);
	

	
	return 0;
}

/* qsort: sort v[left]...v[right] into increasing order */
void kr_qsort(int v[], int left, int right)
{
	int i, last;
	void swap(int v[], int i, int j);
	
	if (left >= right) /* do nothing if array contains */
		return; /* fewer than two elements */
	//printf("%d %d\n",left, (left + right)/2);
	swap(v, left, (left + right)/2); /* move partition elem */
	last = left; /* to v[0] */
	printf("left = last = %d\n",last);
	for (i = left + 1; i <= right; i++) /* partition */
		if (v[i] < v[left]){
			//printf("i = %d, last = %d\n",i, last);
			swap(v, ++last, i);
		}
	swap(v, left, last); /* restore partition elem */
	kr_qsort(v, left, last-1);
	kr_qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
	printf("i = %d, j = %d\n",i,j);
	int temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
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

void itoa_rec(int n, char s[])
{
	if (n < 0) {
		s[i++] = '-';
		n = -n;
	}
	if (n / 10)
		printd(n / 10);
	s[i++] = (n % 10) + '0';
	s[i] = '\0';
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