/*
K&R Ch5.11,p.98
Sorting numerically lines of text
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define ALLOCSIZE 10000 /* size of available space */



int my_getline(char *, int);
char *alloc(int);
int my_readlines(char *lineptr[], int nlines);
void my_writelines(char *lineptr[], int nlines);
//void my_qsort(char *lineptr[], int left, int right);
void my_qsort_n(void *lineptr[], int left, int right, int (*comp)(void *, void *)); // last argument was added to pass a pointer to fun (num or alpha)
int my_numcmp(char *, char *); // new for numerical sorting, equivalent to strcmp
int my_strcmp(char *, char *);
void swap(void *v[], int i, int j);


char *lineptr[MAXLINES]; /* pointers to text lines */
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

/* sort input lines */
int main(int argc, char *argv[])
{
	int nlines; /* number of input lines read */
	int numeric = 0; /* 1 if numeric sort */
	
	if (argc > 1 && strcmp(argv[1], "-n") == 0)
		numeric = 1;
	
	if ((nlines = my_readlines(lineptr, MAXLINES)) >= 0) {
		//my_qsort(lineptr, 0, nlines-1);
		my_qsort_n((void**) lineptr, 0, nlines-1, (int (*)(void*,void*))(numeric ? my_numcmp : my_strcmp));
		my_writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}
/* my_readlines: read input lines */
int my_readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;
	while ((len = my_getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0'; /*n delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}
/* my_writelines: write output lines */
void my_writelines(char *lineptr[], int nlines)
{
	int i;
	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

/* 
// alternative version of my_writelines
void my_writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}
*/ 

/* my_getline: read a line into s, return length */
int my_getline(char s[],int lim)
{
	int c, i;
	for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* my_qsort: sort v[left]...v[right] into increasing order 
void my_qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);
	if (left >= right) // do nothing if array contains
		return; // fewer than two elements
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0) //strcmp added 
			swap(v, ++last, i);
	swap(v, left, last);
	my_qsort(v, left, last-1);
	my_qsort(v, last+1, right);
}*/

/* qsort: sort v[left]...v[right] into increasing order */
void my_qsort_n(void *v[], int left, int right, int (*comp)(void *, void *))
{
	int i, last;
	void swap(void *v[], int, int);
	if (left >= right) /* do nothing if array contains */
		return; /* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	my_qsort_n(v, left, last-1, comp);
	my_qsort_n(v, last+1, right, comp);
}

/* swap: interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
	//char *temp;
	void *temp; //this changed from 073
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

char *alloc(int n) /* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
		allocp += n;
		return allocp - n; /* old p */
	} else /* not enough room */
		return 0;
}


/* numcmp: compare s1 and s2 numerically */
int my_numcmp(char *s1, char *s2)
{
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int my_strcmp(char *s, char *t)
{
	int i;
	for (i = 0; s[i] == t[i]; i++)
		if (s[i] == '\0')
			return 0;
	return s[i] - t[i];
}