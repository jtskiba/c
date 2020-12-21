/* Takes input and print the longest line of all (each is separated in the input by newline */

#include <stdio.h>

#define MAXLINE 1000 /* max input line size*/

int max;                /* max length seen so far */
char line[MAXLINE];     /* current input line */
char longest[MAXLINE];   /* longest line saved here */

int getline(void);
void copy(void);

/* print longest input line; specialised version */
int main()
{
    int len;
    extern int max;
    extern char longest [MAXLINE];

    max = 0;
    while ((len = getline()) > 0)
        if (len > max)
        {
            max = len;
            copy();
        }
    if (max > 0) /* there was a line */
        printf("%s\n", longest);
    return 0;
}

/* getline: specialised version */
int getline(void)
{
    int i, c;
    extern char line[];

    for(i = 0; i < MAXLINE - 1 && ((c = getchar()) != EOF) && c != '\n'; ++i)
    {
        line[i] = c;
    }
    line[i] = '\0';
    return i;
}

/* copy: specialised version */
void copy(void)
{
    int i;
    extern char line[], longest[];

    i = 0;
    while ((longest[i] = line[i]) != '\0')
        ++i;
}
