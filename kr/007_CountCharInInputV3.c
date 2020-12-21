//
//// This program counts number of chars in input
#include <stdio.h>

main(){
    long nc;

    nc = 0;
    while (getchar() != EOF) /* no need for brackets when only 1 line of code */
        ++nc;
    printf("%ld\n", nc); /* enter will be counted as another letter */
}
