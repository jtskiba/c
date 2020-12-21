/*
K&R Ch5, ex5-1 Pointers, p.81
As written, getint treats a + or - not followed by a digit as a valid
representation of zero. Fix it to push such a character back on the input.

i.e. if you just feed + to below, then you get positive outcome and int is 0

*/

#include <ctype.h>
#include <stdio.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int);
int getint(int *pn);
int getint_fix(int *pn);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int main(void)
{
	int mynum, outcome;
	
	
	outcome = getint_fix(&mynum);
	printf("outcome = %d, int = %d\n", outcome, mynum);
	
	return 0;
}

int getint_fix(int *pn)
{
	int c, sign;
	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	if (isdigit(c)){
		for (*pn = 0; isdigit(c); c = getch())
			*pn = 10 * *pn + (c - '0');
		*pn *= sign;
		if (c != EOF)
			ungetch(c);
		return c;
	}
	else{
		if (c != EOF){
			ungetch(c);
			return 0;
		}
		else
			return 0;
	}
}


/* getint: get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign;
	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}




int getch(void) /* get a (possibly pushed-back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

