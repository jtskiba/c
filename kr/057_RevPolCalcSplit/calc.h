/*
K&R Ch4.5, Header files

In reverse Polish notation, each operator follows its operands; 
an infix expression like
(1 - 2) * (4 + 5)

is entered as
1 2 - 4 5 + *

Parentheses are not needed; the notation is unambiguous as long as we 
know how many operands each operator expects.
*/

#define NUMBER '0' /* signal that a number was found */


void push(double);
double pop(void);
int getop(char []);
int getch(void);
void ungetch(int);

