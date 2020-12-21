#include <stdio.h>
#include <string.h>

#define MAXLEN 100
#define MATCH 0
#define INSERT 1
#define DELETE 2


/* Skiena section 8.2 Dynamic programming - Approximate String Matching

in section 8.2.4 Skiena also gives modifications such that certain combinations are penalised more than others, see p.288
 */

typedef struct cell{
	int cost;
	int parent;
} cell;

cell m[MAXLEN+1][MAXLEN+1]; //dynamic programming table


int indel(char s){
	return(1);
}

int match(char a, char b){
	if (a == b) return(0);
	else return(1);
}

int row_init(int i){
	m[0][i].cost = i;
	if (i>0)
		m[0][i].parent = INSERT;
	else
		m[0][i].parent = -1;
}

int column_init(int i){
	m[i][0].cost = i;
	if (i>0)
		m[i][0].parent = DELETE;
	else
		m[i][0].parent = -1;
}

void goal_cell(char *s, char *t, int *i, int *j){
	*i = strlen(s)-1;
	*j = strlen(t)-1;
}

void insert_out(char *t, int j){
	printf("I");
}

void delete_out(char *s, int i){
	printf("D");
}

void match_out(char *s, char *t, int i, int j){
	if (s[i]==t[j])
		printf("M");  //match
	else
		printf("S");  //substitute
}

void reconstruct_path(char *s, char *t, int i, int j){
	if (m[i][j].parent == -1) return;
	
	if (m[i][j].parent == MATCH){
		reconstruct_path(s,t,i-1,j-1);
		match_out(s,t,i,j);
		return;
	}
	
	if (m[i][j].parent == INSERT){
		reconstruct_path(s,t,i,j-1);
		insert_out(t,j);
		return;
	}
	
	if (m[i][j].parent == DELETE){
		reconstruct_path(s,t,i-1,j);
		delete_out(s,i);
		return;
	}
	
}

// dynamic programming version
int string_compare(char *s, char *t){
	int i,j,k;
	int opt[3];
	
	for (i=1;i<MAXLEN;i++){
		row_init(i);
		column_init(i);
	}
	
	for (i=1; i<strlen(s); i++){
		for (j=1; j<strlen(t); j++){
			opt[MATCH]  = m[i-1][j-1].cost + match(s[i],t[j]);
			opt[INSERT] = m[i][j-1].cost + indel(t[j]);
			opt[DELETE] = m[i-1][j].cost + indel(s[i]);
			
			m[i][j].cost = opt[MATCH];
			m[i][j].parent = MATCH;
			for (k=INSERT;k<=DELETE;k++)
				if(opt[k] < m[i][j].cost){
					m[i][j].cost = opt[k];
					m[i][j].parent = k;					
				}
		}
	}
	goal_cell(s, t, &i, &j);
	return(m[i][j].cost);
}



int main(void){
	char *t = "Thou-shalt-not";
	char *p = "You-should-not";
	printf("t=%s\n",t);
	printf("p=%s\n",p);
	printf("cost=%d\n",string_compare(p, t));    // much faster!! than the recursive exhaustive
	reconstruct_path(p, t, strlen(p)-1,strlen(t)-1);
}
