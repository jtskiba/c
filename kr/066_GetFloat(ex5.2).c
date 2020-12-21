/*
K&R Ch5, ex5-2 Pointers, p.81
Write getfloat, the floating-point analog of getint. What type does getfloat
return as its function value?

*/

#include <ctype.h>
#include <stdio.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int);
int getint(int *pn);
int getint_fix(int *pn);
int getfloat(float *pn);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int main(void)
{
	int mynum, outcome;
	float myfloat;
	//int myfloat;
	
	outcome = getfloat(&myfloat);
	printf("outcome = %d, int = %f\n", outcome, myfloat);
	
	return 0;
}

int getfloat(float *pn)
{
	int c, sign;
	float power;
	
	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1.0 : 1.0;
	if (c == '+' || c == '-')
		c = getch();
	if (isdigit(c)){
		for (*pn = 0.0; isdigit(c); c = getch())
			*pn = 10.0 * *pn + (float)(c - '0');
		// from here to debug
		if (c == '.'){
			c = getchar();
			for (power = 1.0; isdigit(c); c = getch()) {
				*pn = 10.0 * *pn + (float)(c - '0');
				power *= 10.0;
			}
			*pn = *pn * sign / power;
			if (c != EOF)
				ungetch(c);
			return c;
		}
		else {
		
			if (c != EOF){
				ungetch(c);
				return 0;
			}
			else{
				*pn = *pn * sign / power;
				return c;
			}					
		}
		///////// until here to debug
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

