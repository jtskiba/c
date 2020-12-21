// Ex1-12 (p.21 K&R) - Write a program that prints its input one word per line

#include <stdio.h>
#define IN 1
#define OUT 0

void main(void){
    int c, state;

    state = OUT;
    while ((c = getchar()) != EOF){
        if (c != ' ' && c != '\n' && c != '\t')
        {
            putchar(c);
            state = IN;
        }
        else if (state == IN)
        {
            printf("\n");
            state = OUT;
        }
    }
}
