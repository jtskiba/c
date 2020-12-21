// Copy input to output, replacing each string of one or more blanks by a single blank (Exercise 1.9, p.20)
#include<stdio.h>

main()
{
    int c, sum_blanks;

    sum_blanks = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            ++sum_blanks;
            if (sum_blanks == 1)
                putchar(c);
        }
        else
        {
            sum_blanks = 0;
            putchar(c);
        }
    }
}
