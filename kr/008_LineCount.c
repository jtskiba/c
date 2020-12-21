// Count number of lines

#include <stdio.h>

main()
{
    int space, c;
    space = 0;

    while ((c = getchar()) != EOF)
        if (c == '\n') /* Important: this is char so need to use '' rather than "" */
            ++space;
        //c = getchar();
    printf("\nNo is: %d\n", space);
}
