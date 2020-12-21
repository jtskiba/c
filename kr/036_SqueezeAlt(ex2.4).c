/*
K&R ex2.4, p.44 

Write an alternative version of squeeze(s1,s2) that deletes each character in
s1 that matches any character in the string s2.
*/

#include<stdio.h>

void squeeze(char s[], int c);
void alt_squeeze(char s1[], char s2[]);
void alt_squeeze2(char s1[], char s2[]);

int main(void)
{        
	//int c = 'a';
	char s1[100];
	char s2[100];

	printf("Type s1:\n");
	gets(s1);
	printf("\nType s2:\n");
	gets(s2);
	
	//squeeze(s1,c);
	alt_squeeze(s1,s2);
	printf("%s\n", s1);
 
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

/*alternative version of above. It deletes each character in
s1 that matches any character in the string s2. */
void alt_squeeze(char s1[], char s2[])
{
	int i, j, k, c;
	
	for (i = j = k = 0; s1[i] != '\0'; i++){
		while ((c = s2[k++]) != '\0'){
			if (s1[i] != c)
				s1[j] = s1[i];
			else{
				j--;
				break;
				}
		}
		j++;
		k = 0;		
	}
	s1[j] = '\0';
}

void alt_squeeze2(char s1[], char s2[])
{
	int i, j, k, c;
	
	for (i = 0; s2[i] != '\0'; i++)
		squeeze(s1,s2[i]);
}


