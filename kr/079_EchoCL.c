/*
K&R Ch5-10 Command Line Arguments
Echo

you have to compile, i.e. e.g. gcc -o o hello world
then ./o hello world

*/

#include <stdio.h>

/* echo command-line arguments; 2nd version */
int main(int argc, char *argv[])
{
	while (--argc > 0)
		//printf("%s%s", *++argv, (argc > 1) ? " " : "");
		printf((argc > 1) ? "%s " : "%s", *++argv);
	printf("\n");
	return 0;
}

//alternative versions above

