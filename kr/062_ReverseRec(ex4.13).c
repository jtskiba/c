/*
K&R ex4.13 Recursion, p.74
Write a recursive version of the function reverse(s), which reverses the
string s in place.
*/

#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void itoa(int n, char s[]);
void printd(int n);
void itoa_rec(int n, char s[]);
void kr_qsort(int v[], int left, int right);
void swap(int v[], int i, int j);
void reverse_rec(char s[], int x, int y);

int m = 0;

int main(void)
{       	
	char str1[] = "MyName";
	printf("%s\n",str1);
	reverse_rec(str1, 0, strlen(str1)-1);
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
		s[m++] = '-';
		n = -n;
	}
	if (n / 10)
		printd(n / 10);
	s[m++] = (n % 10) + '0';
	s[m] = '\0';
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

void reverse_rec(char s[], int x, int y)
{
	int c;

	if (x < y){
		c = s[x];
		s[x] = s[y];
		s[y] = c;
		reverse_rec(s, ++x, --y);
	}
	else
		return;
}