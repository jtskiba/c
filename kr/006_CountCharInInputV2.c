
// This program counts number of chars in input
#include <stdio.h>

int main(){
    int nc;
    nc = 0;

    for (nc; getchar()!=EOF ; ++nc){
        ; /* empty loop, no need for anything */
    }
    printf("%ld\n",nc);
    return 0;
}
