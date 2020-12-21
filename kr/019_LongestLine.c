/* Takes input and print the longest line of all (each is separated in the input by newline */

#include <stdio.h>

#define MAXLINE 1000 /* max input line size*/

int getline(char s[], int maxline); /* note, need to have char's here, not int's */
int copy(char from[], char to[]);

int main()
{
    int len, max;
    char line[MAXLINE];
    char longest [MAXLINE];

    max = 0;
    while ((len = getline(line, MAXLINE)) > 0) /* note > 0 until there is new line, also no [] after line */
        if (len > max)
        {
            max = len;
            copy(line, longest);
        }
    if (max > 0) /* to make sure some input was made initially */
        printf("%s\n", longest); /* note no [] after longest */

    return 0;
}

/* getline: get input into s up to limit, return length */
int getline(char s[], int limit)
{
    int i, c;

    for(i = 0; i < limit - 1 && ((c = getchar()) != EOF) && c != '\n'; ++i)
    {
        s[i] = c;
    }
    s[i] = '\0';
    return i;
}

/* copy: copy string from from[] to to[], assume to[] is big enough */
int copy(char from[], char to[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
    return 0; /*dummy return */
}
