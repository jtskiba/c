// Ex1-13. Write a program to print a histogram of the lengths of words in its input
// Do the vertical histogram (harder)

#include <stdio.h>
#define IN 1
#define OUT 0
#define HIST_LEN 10

main()
{
    /* declaring variables */
    int i, j, max, c, status, count;
    int hist[10]; /* this will hold number of words of length 1, 2, 3, .., 9 and other (>=10) */

    /* initialise variables */
    for (i = 0; i <= HIST_LEN - 1; ++i)
        hist[i] = 0;
    count = 0;
    status = OUT;

    /* read input from keyboard - sentences that you want to show in histogram
       also allocate it to hist[] array, i.e. frequencies of words of length 1,2,...9 and other
    */
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
    /* finding max frequency of lengths of words */
    max = hist[0];
    for (i = 1; i <= HIST_LEN - 1; ++i)
        if (max < hist[i])
            max = hist[i];


    /* printing histogram bars
    first go from max, find which one it is, and print X for it, and blank for others */
    for (i = max; i >= 1; --i)
    {
        for (j = 0; j <= HIST_LEN - 1; ++j)
            if (hist[j] >= i) /* this is greater or equal as if it was equal only, it would print only top X */
                printf("X ");
            else
                printf("  ");
            printf("\n");
    }
    /* printing histogram labels at the bottom */
    for (j = 0; j <= HIST_LEN - 2; j++)
        printf("%d ", j + 1);
    printf("other \n");

}
