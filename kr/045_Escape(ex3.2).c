/*
K&R ex3.2 p.53

Write a function escape(s,t) that converts characters 
like newline and tab into visible escape sequences like 
\n and \t as it copies the string t to s. Use a switch. 
Write a function for the other direction as well, 
converting escape sequences into the real characters.

*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>


int binsearch(int x, int v[], int n);
int newbinsearch(int x, int v[], int n);


int main(void)
{        

	char c;
	
	
	while ((c = getchar()) != EOF){
		switch (c) {
			case '\n':
				putchar('\\');
				putchar('n');
				break;
			case '\t':
				putchar('\\');
				putchar('t');
				break;
			default:
				putchar(c);
				break;
		}
	}
	
	
	return 0;
}



/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
/* v is in ascending order of values */
int binsearch(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	
	while (low <= high) {
		mid = (low+high)/2;
		if (x < v[mid])
			high = mid + 1;
		else if (x > v[mid])
			low = mid + 1;
		else /* found match */
			return mid;
	}
	return -1; /* no match */
}

int newbinsearch(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	mid = (low+high)/2;
	
	while ((low <= high) && (x != v[mid])) {
		if (x < v[mid])
			high = mid + 1;
		else
			low = mid + 1;
		mid = (low+high)/2;
	}
	if (x == v[mid])
		return mid; /*match */
	else 
		return -1; /* no match */
}
