// Ex1-13. Write a program to print a histogram of the lengths of words in its input
// Do the horizontal histogram

#include <stdio.h>
#define IN 1
#define OUT 0
#define HIST_LEN 10

main()
{
    int i, j, c, status, count;
    int hist[10]; /* this will hold number of words of length 1, 2, 3, .., 9 and other (>=10) */

    for (i = 0; i <= HIST_LEN - 1; ++i)
        hist[i] = 0;
    count = 0;
    status = OUT;
    while((c = getchar()) != EOF)
    {
        if (c != ' ' && c != '\n' && c != '\t')
        {
            status = IN;
            count += 1;
        }
        else if (status == IN)
        {
            if (count <= HIST_LEN - 1)
                hist[count - 1] += 1;
            else
                hist[HIST_LEN - 1] += 1;
            count = 0;
            status = OUT;
        }

    }
    for (i = 0; i <= HIST_LEN - 1; ++i)
    {
        if (i <= HIST_LEN - 2)
            printf("%5d | ", i + 1);
        else
            printf("other | ");
        for (j = 0; j < hist[i]; ++j)
            printf("X");
        printf("\n");
    }
}
