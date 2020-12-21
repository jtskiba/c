// This program counts number of chars in input
#include <stdio.h>

int main(){
    int nc;
    int c = getchar();

    while (c != EOF){
        nc++;
        c = getchar(); /* this line is important when you have c in while and c = getchar before while loop */
    }
    printf("%ld\n",nc-3); /*take away -3 (1 for \n and 2 for ctrl+z
                                          also, %ld means long integer */
    return 0;
}
