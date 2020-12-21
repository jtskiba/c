// Exercise 1.8, p.20
// Write a program to count blanks, tabs and newlines

#include<stdio.h>

main()
{
    int c, sum;

    sum = 0;
    while((c = getchar()) != EOF)
        if ((c == ' ') || (c == '\n') || (c == '\t'))
            ++sum;
        printf("%d\n", sum);

}
