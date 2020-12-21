/*
K&R Ch6, p.110, ex6.4
Write a program that prints the distinct words in its input sorted into decreasing
order of frequency of occurrence. Precede each word by its count.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define BUFSIZE 100
#define NKEYS 11 //need to update manually as you change the number of items in keytab
#define MAXLINES 100


struct tnode { /* the tree node: */
	char *word; /* points to the text */
	int count; /* number of occurrences */
	char lines[MAXLINES]; //added to show string of lines where the word is shown
	struct tnode *left; /* left child */
	struct tnode *right; /* right child */
};

struct key {
	char *word;
	int count;
};


void tree_swap(char *v[], int i, int j);
void tree_qsort(char *lineptr[], int left, int right);

void swap(char *v[], int i, int j);
void my_qsort(char *lineptr[], int left, int right);


struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
char *my_strdup(char *);
void treeprint(struct tnode *);
int getword(char *, int);
int getword(char *word, int lim);
int binsearch(char *word, struct key tab[], int n);
//struct key *binsearch(char *, struct key *, int);
int getword(char *word, int lim);
int getch(void);
void ungetch(int c);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int lineno = 1; // to count line numbers globally


/* word frequency count */
int main(void)
{	
	struct tnode *root;
	char word[MAXWORD];
	root = NULL;
	
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);
	
	return 0;
}

/* binsearch: find word in tab[0]...tab[n-1]               /// PREVIOUS VERSION*/
int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;
	
	low = 0;
	high = n - 1;
	
	while (low <= high) {
		mid = (low+high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

/* binsearch: find word in tab[0]...tab[n-1]      //////// POINTER VERSION
struct key * binsearch(char *word, struct key *tab, int n)
{
	int cond;
	struct key *low = &tab[0];
	struct key *high = &tab[n];
	struct key *mid;
	while (low < high) {
		mid = low + (high-low) / 2;
		if ((cond = strcmp(word, mid->word)) < 0)
			high = mid;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return NULL;
}*/


/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	
	while (isspace(c = getch())){
		if (c == '\n') //added to count lines
			lineno++;
		;	
	}

	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	
	for ( ; --lim > 0; w++){
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}

int getch(void) /* get a (possibly pushed-back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s, lines: %s\n", p->count, p->word, p->lines); //added last item to show line no's where the word is shown
		treeprint(p->right);
	}
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;
	char temp[100]; //temp so that i can paste current line number into it, and then append this temp to current string of all line numbers
	if (p == NULL) { /* a new word has arrived */
	p = talloc(); /* make a new node */
		p->word = my_strdup(w);
		p->count = 1;
		//p->lines = "1234";
		itoa(lineno,p->lines,10); //add int lineno (current line) to p->lines (10 means number in decimals)
		strcat(p->lines,", "); // add comma at the end of the string
		p->left = p->right = NULL;
	} 
	else if ((cond = strcmp(w, p->word)) == 0){
		p->count++; /* repeated word */
		itoa(lineno,temp,10); //storing lineno in temp (10 means show number in decimals, 2 would mean binary)
		strcat(p->lines,temp); //concatenate p->lines with temp
		strcat(p->lines,", "); // concatenate p->lines with comma at the end
	}
	else if (cond < 0) /* less than into left subtree */
		p->left = addtree(p->left, w);
	else /* greater than into right subtree */
		p->right = addtree(p->right, w);
	return p;
}

struct tnode *rebuild(struct tnode *new, struct tnode *old)
{
	int cond;
	char temp[100]; //temp so that i can paste current line number into it, and then append this temp to current string of all line numbers
	if (old->left == NULL) { /* we are at the end of nodes */
	/*
		new = talloc(); // make a new node
		new->word = my_strdup(w);
		new->count = 1;
		//p->lines = "1234";
		itoa(lineno,new->lines,10); //add int lineno (current line) to p->lines (10 means number in decimals)
		strcat(new->lines,", "); // add comma at the end of the string
		new->left = new->right = NULL;
	*/
	} 
	else if (old->word == NULL) == 0){
		new->count++; /* repeated word */
		itoa(lineno,temp,10); //storing lineno in temp (10 means show number in decimals, 2 would mean binary)
		strcat(new->lines,temp); //concatenate p->lines with temp
		strcat(new->lines,", "); // concatenate p->lines with comma at the end
	}
	else if (cond < 0) /* less than into left subtree */
		new->left = addtree(new->left, w);
	else /* greater than into right subtree */
		new->right = addtree(new->right, w);
	return new;
}




//strdup merely copies the string given by its argument into a safe place, obtained by a call on
//malloc:
char *my_strdup(char *s) /* make a duplicate of s */
{
	char *p;
	p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}

/* my_qsort: sort v[left]...v[right] into increasing order */
void my_qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);
	if (left >= right) /* do nothing if array contains */
		return; /* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0) //strcmp added 
			swap(v, ++last, i);
	swap(v, left, last);
	my_qsort(v, left, last-1);
	my_qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/* my_qsort: sort v[left]...v[right] into increasing order */
void tree_qsort(char *v[], int left, int right)
{
	int i, last;
	void tree_swap(char *v[], int i, int j);
	if (left >= right) /* do nothing if array contains */
		return; /* fewer than two elements */
	tree_swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0) //strcmp added 
			tree_swap(v, ++last, i);
	tree_swap(v, left, last);
	tree_qsort(v, left, last-1);
	tree_qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void tree_swap(struct tnode *p, int i, int j)
{
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

