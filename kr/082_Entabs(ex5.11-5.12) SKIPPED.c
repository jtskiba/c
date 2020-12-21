/*
K&R Ch4,p.64

In reverse Polish notation, each operator follows its operands; 
an infix expression like
(1 - 2) * (4 + 5)

is entered as
1 2 - 4 5 + *

Parentheses are not needed; the notation is unambiguous as long as we 
know how many operands each operator expects.
*/

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h> /* for isdigit()? */


#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100


int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

/* reverse Polish calculator */
int main(int argc, char *argv[])
{
	int type;
	double op2, op1;
	char s[MAXOP];
	
	
	while (--argc > 0) {
		*argv++;
		switch ((*argv)[0]) {
			case '+':
				//printf("^\n");
				push(pop() + pop());
				break;
			case 'x': //times
				printf("$\n");
				//op2 = pop();
				//op1 = pop() * op2;
				//printf("%f\n", op1);
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			case '=':
				printf("\t%.8g\n", pop());
				break;
				
			default:
				//case NUMBER:
				//printf(".\n");
				//printf(".%s\n",*argv);
				//printf(".%f\n",atof(*argv));
				push(atof(*argv));
				break;
				//printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}


/* push: push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}


/* getop: get next character or numeric operand */
int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c; /* not a number */
	i = 0;
	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.') /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
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