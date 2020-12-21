// Copy input to output, replacing each string of one or more blanks by a single blank (Exercise 1.9, p.20)
// to finish - not sure about backspace
#include<stdio.h>

main()
{
    int c;

    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            putchar('\\');
            putchar('\\t');
        }
        else if (c == '\b')
        {
            putchar('\\');
            putchar('\\b');
        }
        else if (c == '\\')
        {
            putchar('\\');
            putchar('\\');
        }

        else
            putchar(c);
    }
}
