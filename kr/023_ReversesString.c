/* Write a fn reverse(s) that reverses the character string s. Use it to write a program that reverses
    its input a line at a time. This is ex1-19 on p.31 K&R*/

#include <stdio.h>

#define MAXLINE 1000 /* max input line size*/
#define TARGET 1 /* lines above this target will be remembered and printed */

int getline(char s[], int maxline); /* note, need to have char's here, not int's */
int copy(char from[], char to[]);
int reverse(char s[]);

int main()
{
    int i, len, max, iter;
    char line[MAXLINE];
    char above_target[MAXLINE][MAXLINE];

    max = iter = 0;
    while ((len = getline(line, MAXLINE)) > 0) /* note > 0 until there is new line, also no [] after line */
        if (len > TARGET)
        {
            copy(line, above_target[iter]);
            ++iter;
        }
    if ((iter > 0) || (len > 0)){ /* to make sure some input was made initially */
        for (i = 0; i < iter; ++i){
            reverse(above_target[i]);
            printf("%s\n",above_target[i] ); /* note no [] after longest */
        }

    }
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

/* reverse char s, being until \0 is hit, so will reverse lines, not words */
int reverse(char s[])
{
    int i,j, k;
    char temp[MAXLINE];

    i = j = k = 0;
    while (s[i] != '\0'){
        ++i;
    }

    for (k=i-1; k >= 0; --k){
        temp[j] = s[k];
        ++j;
    }
    temp[j] = '\0';
    copy(temp,s);
    return 0;
}
