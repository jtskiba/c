// Ex1-14. Print a histogram of characters

#include <stdio.h>
#define HIST_LEN 256


main()
{
    int i, j, c, status, count;
    int hist[HIST_LEN]; // this will hold number of characters numbers

    for (i = 0; i < HIST_LEN; ++i)
        hist[i] = 0;
    count = 0;


    // Prints out all characters and their ANSCII code up to 250
    //for (i = 0; i < 250; ++i)
    //    printf("%d = %c\n", i, i);

    while((c = getchar()) != EOF)
    {
        for (i = 1; i <= HIST_LEN - 1; ++i)
            if (c == i)
                hist[i] += 1;
    }

    for (i = 2; i <= HIST_LEN - 1; ++i)
    {
        if (hist[i] >= 1 && i != '\n' && i != '\t' && i != ' ')
        {
            printf("%5c | ", i);
            for (j = 1; j <= hist[i]; ++j)
                printf("X");
            printf("\n");
        }

    }
}


