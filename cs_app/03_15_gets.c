#include <stdio.h>

/*implementation of library function gets*/
char *gets(char *s){
	int c;
	char *dest = s;
	
	while ((c = getchar()) != '\n' && c != EOF)
		*dest++ = c;
	if (c == EOF && dest == s)
		/* no character read */
		return NULL;
	*dest++ = '\0'; /* terminate string*/
	return s;
}

/* read input line and write it back*/
void echo(){
	char buf[8]; /*way too small!*/
	gets(buf);
	puts(buf);
}
