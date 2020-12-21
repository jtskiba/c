/* Takes input and print the longest line of all (each is separated in the input by newline */
/* Modify previous program so that arbitrarily long length of line can be used, i.e. no MAXLINE */
/* this is Ex 1-16 on p.30 */

#include <stdio.h>

int getline();
int copy(char from[], char to[]);

int main()
{
    int len, max;

    max = 0;
    while ((len = getline()) > 0) /* note > 0 until there is new line, also no [] after line */
        if (len > max)
            max = len;
    if (max > 0) /* to make sure some input was made initially */
        printf("%d\n", max); /* note no [] after longest */

    return 0;
}

/* getline: get input into s up to limit, return length */
int getline()
{
    int i, c;

    i = 0;
    while(((c = getchar()) != EOF) && c != '\n')
        ++i;
    return i;
}

