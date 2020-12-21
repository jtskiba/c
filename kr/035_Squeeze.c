/*
K&R Ch2.7, p44 
Write a function squeeze(s,c), which removes all occurrences
of the character c from the string s.
*/

#include<stdio.h>

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
/*squeeze: delete all c from s*/
void squeeze(char s[], int c)
{
	int i, j;
	
	for (i = j = 0; s[i] != '\0'; i++)
		if (s[i] != c)
			s[j++] = s[i];
	s[j] = '\0';
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
