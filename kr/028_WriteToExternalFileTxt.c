
#include<stdio.h>

int main(void)
{
    FILE *ptr_file;
    int x;

    ptr_file = fopen("output.txt","w");

    if (!ptr_file)
        return 1;

    for (x = 11; x <= 14; x++)
        fprintf(ptr_file, "%d\n", x);

    fclose(ptr_file);

    return 0;
}

