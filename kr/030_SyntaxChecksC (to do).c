/*
K&R Ex 1-24, p.34.
Check a C program for rudimentary syntax errors like unbalanced parantheses, brackets and braces
Dont forget about quotes, both single and double, escape sequences, and comments.
(This program is hard if you do it in full generality)
*/
#include<stdio.h>
#define MAXLINE 10000

int main(void)
{
    FILE *ptr_file1;

    char buffer[MAXLINE];

    int c, i, j, t;
    int status1, in_string; // if you are in '/*  */' type of comments

    ptr_file1 = fopen("input_029.txt","r");

    i = 0;
    if (ptr_file1 == NULL){
        printf("Error\n");
        return -1;
    } do {
        c = fgetc(ptr_file1);
        if (feof(ptr_file1)){
            buffer[i] = '\0';
            break;
        }
    //printf("%c",c);
    buffer[i] = c;
    ++i;
    } while (1);

    status1 = in_string = 0; // out, otherwise 1 which is in

    // this removes comments from the input.txt
    for (i = 0; i <= MAXLINE - 1; ++i)
        {
            // check if you are in sting
            if ((buffer[i] == '"') && (status1 == 0) && (in_string == 0))
            {
                in_string = 1;
            }
            else if ((buffer[i] == '"') && (buffer[i-1] != '\\') && (in_string == 1))
            {
                in_string = 0;
            }
    //printf("Enter \" /* coefficients */ a, b and c: ");
            // remove comments after double /
            if ((buffer[i] == '/') && (buffer[i+1] == '/') && (status1 == 0) && (in_string == 0))
            {
                t = i;
                while (buffer[t] != '\n') //remove up to new line
                {
                    buffer[t] = ' '; // removing to me means overriding with blank
                    ++t;
                }
            }

            // remove comments in /*   */
            if ((buffer[i] == '/') && (buffer[i+1] == '*') && (status1 == 0) && (in_string == 0))
            {
                status1 = 1; // keeps track of when comment quotes are open
                buffer[i] = buffer[i+1] = ' ';
            }
            else if ((buffer[i] == '*') && (buffer[i+1] == '/') && (status1 == 1))
            {
                buffer[i] = buffer[i+1] = ' ';
                status1 = 0;
            }
            else if ((status1==1) && (buffer[i] != '\n'))
            {
                buffer[i] = ' ';
            }
        }

    printf("\n\n");
    for (i = 0; (i <= MAXLINE - 1) && (buffer[i] != '\0'); ++i)
        printf("%c",buffer[i]);

    fclose(ptr_file1);
    return 0;

}

