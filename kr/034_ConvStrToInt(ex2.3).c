/*
K&R Ex2.3 
Write a function htoi(s), which converts a string of hexadecimal digits
(including an optional 0x or 0X) into its equivalent integer value. 
The allowable digits are 0 through 9, a through f, and A through F.
*/

#include<stdio.h>
#include<string.h>
#include<ctype.h>

int atoi(char s[]);
int htoi(char s[]);

int main(void)
{        
	int number_rep;
	char str[10];
	char c;
	
	c='0'; printf("ASCII for %c is %d\n",c,c);
	c='1'; printf("ASCII for %c is %d\n",c,c);
	c='9'; printf("ASCII for %c is %d\n",c,c);
	c='a'; printf("ASCII for %c is %d\n",c,c);
	c='b'; printf("ASCII for %c is %d\n",c,c);
	c='c'; printf("ASCII for %c is %d\n",c,c);
	

	printf("Enter string number to convert to int (<len=10):\n");
	gets(str);
	
	number_rep = htoi(str);
    printf("%x\n", number_rep);
 
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

/*htoi: convert s to hex*/
int htoi(char s[])
{
	int i, start, n;
	n = 0;
	start = 0;
	
	if (strlen(s) > 2)
	{
		if(s[0] == '0' && toupper(s[1]) == 'X')
			start = 2;
		else
			start = 0;
	}
	
	for (i = start; (toupper(s[i]) >= '0' && toupper(s[i]) <= '9') ||
		(toupper(s[i]) >= 'A' && toupper(s[i]) <= 'F'); i++)
		if (toupper(s[i]) >= '0' && toupper(s[i]) <= '9')
			n = 16 * n + (toupper(s[i]) - '0');
		else
			n = 16 * n + (10 + (toupper(s[i]) - 'A'));
	
	return n;
}
