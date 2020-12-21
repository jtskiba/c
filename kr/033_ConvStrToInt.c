/*
K&R Ch2.7 
ATOI Convert string to integer as given in the text
*/

#include<stdio.h>
#include<string.h>

int atoi(char s[]);

int main(void)
{        
	int number_rep;
	char str[10];
	
	printf("Enter string number to convert to int (<len=10):\n");
	gets(str);
	
	number_rep = atoi(str);
    printf("%d\n", number_rep);
 
    return 0;
}

/*atoi: convert s to integer*/
int atoi(char s[])
{
	int i, n;
	n = 0;
	for (i = 0; s[i] >= '0' && s[i] <= '9'; i++)
		n = 10 * n + (s[i] - '0');
	return n;
}

