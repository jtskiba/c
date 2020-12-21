// Counts number of newlines, new words, characters
// to execute press enter and then ctrl+z and enter

#include <stdio.h>

#define IN 1
#define OUT 0


void main(void){
    int state, c, nl, nw, nc;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF){
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == '\n' || c == ' ' || c == '\t')
            state = OUT;
        else if (state == OUT){
            state = IN;
            ++nw;
        }
    }
    printf("new lines: %d, new words: %d, characters: %d\n", nl, nw, nc);
}
