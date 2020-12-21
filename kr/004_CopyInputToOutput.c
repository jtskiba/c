// This program records char (can be multple) and prints it back when you hit ENTER
// It will terminate when EOF, i.e. Ctrol+Z (it is like -1)
#include <stdio.h>

int main(){
    int c;

    c = getchar();
    while (c != EOF){
        // EOF is here Ctrl+Z
        putchar(c);
        c = getchar();
    }
    // Check the value if EOF
    printf("\nEOF is %d\n", EOF);
    // Check where below is 0 or 1
    printf("\n%d",getchar() !=  EOF);
    return 0;
}
