/*
K&R ex3.5 p.56

Write the function itob(n,s,b) that converts the integer n into a base b
character representation in the string s. In particular, itob(n,s,16) 
formats s as a hexadecimal integer in s.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

void reverse(char s[]);
void js_itoa(int n, char s[]);
void kr_itoa(int n, char s[]);
void js_itob(int n,char s[], int b);

int main(void)
{       	
	char str1[100];
	//char str2[100];
	int number, base;
	//int number = INT_MIN;
	//printf("INT_MIN is: %d\n", number);
	printf("Enter decimal number to convert to string:\n");
	scanf("%d", &number);
	printf("Enter base of target number string:\n");
	scanf("%d", &base);
	
	js_itob(number, str1, base);
	printf("A string version of decimal %d using base %d is (js): %s\n", number, base, str1);		
	return 0;
}

/* itoa: convert n to characters in s */
void js_itoa(int n, char s[])
{
	int i, sign, flag;
	if (n == INT_MIN)
		flag = 1;
	else
		flag = 0;
	
	if (flag == 0){
		if ((sign = n) < 0) /* record sign */
			n = -n; /* make n positive */
	}
	else
		n = INT_MAX;
			
	i = 0;
	do { /* generate digits in reverse order */
		if (flag = 1 && i == 0)
			s[i++] = ((n % 10) + 1) + '0';
		else
			s[i++] = (n % 10) + '0'; /* get next digit */
	} while ((n /= 10) > 0); /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void kr_itoa(int n, char s[])
{
	int i, sign;
	
	if ((sign = n) < 0) /* record sign */
		n = -n; /* make n positive */
	i = 0;
	do { /* generate digits in reverse order */
		s[i++] = (n % 10) + '0'; /* get next digit */
	} while ((n /= 10) > 0); /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* reverse: reverse string s in place */
void reverse(char s[])
{
	int c, i, j;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}


void js_itob(int n,char s[],int b)
{
	int i, sign, temp;
	if ((sign = n) < 0) /* record sign */
		n = -n; /* make n positive */
				
	i = 0;
	do { /* generate digits in reverse order */
	    temp = (n % b);
	    switch (temp){
	        case 10:
	            s[i++] = 'A'; /* get next digit */
	            break;  
	        case 11:
	            s[i++] = 'B'; /* get next digit */
	            break; 
	        case 12:
	            s[i++] = 'C'; /* get next digit */
	            break;
	        case 13:
	            s[i++] = 'D'; /* get next digit */
	            break;     
	        case 14:
	            s[i++] = 'E'; /* get next digit */
	            break; 	        
	        case 15:
	            s[i++] = 'F'; /* get next digit */
	            break;
	        default:
	            s[i++] = (n % b) + '0'; /* get next digit */
	            break;
	    }
	} while ((n /= b) > 0); /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

