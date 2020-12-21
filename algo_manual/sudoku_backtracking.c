
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Skiena section 7.3 Backtracaking - Sudoku, page 239


*/

#define DIMENSIONS 9
#define CELLS DIMENSIONS*DIMENSIONS
#define MAXCANDIDATES 9


bool finished = false;  //to finish routine at request (here to stop printing when first solution to sudoku is found)

typedef struct point{
	int x;
	int y;
} point;

typedef struct boardtype{
	int m[DIMENSIONS+1][DIMENSIONS+1];  // matrix of board content
	int freecount;   // spaces on board still free
	point move[CELLS+1]; //sequence of moves (x,y) performed to fill in the board
	int sec_free[(DIMENSIONS/3)+1][(DIMENSIONS/3)+1];
} boardtype;

void initialise_board(boardtype *board){
	int i, j; //counter
		
	for (i=1;i<=DIMENSIONS;i++)
		for (j=1;j<=DIMENSIONS;j++)
			board->m[i][j] = 0;
	
	
	for (i=1;i<=DIMENSIONS/3;i++)
		for (j=1;j<=DIMENSIONS/3;j++)
			board->sec_free[i][j] = DIMENSIONS;
	
	board->move[0].x = 0;
	board->move[0].y = 0;
	
	board->freecount = DIMENSIONS*DIMENSIONS;
	
}

void read_board(boardtype *board){
	int i, j;
	int v;
	void fill_square();	
		
	initialise_board(board);
		
	for (i=1; i<=DIMENSIONS; i++){
		for (j=1; j<=DIMENSIONS; j++){
			scanf("%d", &v);
			if (v != 0)
				fill_square(i, j, v, board);
		}
	}
}


void print_board(boardtype *b){
	int i,j; //couter
	
	printf("-------------------------\n");
	for (i=1;i<=DIMENSIONS;i++){
		printf("| ");
		for (j=1;j<=DIMENSIONS;j++){
			printf("%d ", b->m[i][j]);
			if ((j % (DIMENSIONS/3)) == 0)
				printf("| ");
		}
		printf("\n");
		if ((i % (DIMENSIONS/3)) == 0)
			printf("-------------------------\n");
	}
}

void fill_square(int x, int y, int v, boardtype *board){
	int nx, ny;
	point *p;
	p = malloc(sizeof(point));
	p->x = x;
	p->y = y;
	
	board->freecount = board->freecount - 1;
	board->move[CELLS - board->freecount] = *p;
	
	board->m[x][y] = v;
		
	nx = ((x-1)/(DIMENSIONS/3))+1;
	ny = ((y-1)/(DIMENSIONS/3))+1;
	//printf("nx %d ny %d\n",nx, ny);
	board->sec_free[nx][ny] = board->sec_free[nx][ny] - 1;
	
}


void free_square(int x, int y, boardtype *board){
	int nx, ny;
	
	if (board->m[x][y] == 0)
		return; // this x y position on the board is already free
	
	board->freecount = board->freecount + 1;
	
	board->m[x][y] = 0;
		
	nx = ((x-1)/(DIMENSIONS/3))+1;
	ny = ((y-1)/(DIMENSIONS/3))+1;
	//printf("nx %d ny %d\n",nx, ny);
	board->sec_free[nx][ny] = board->sec_free[nx][ny] + 1;
}

void next_square(int *k, int *l, boardtype *board){
	int i, j, start_x, start_y;
	int tx, ty;  // temp x y
	int matrix_min();
	
	matrix_min(board->sec_free, &tx, &ty); // returns quadrant x 1/2/3 and y 1/2/3    
	//11 12 13
	//21 22 23
	//31 32 33
	
	// just in case matrix_min return default answet 0 0 
	/*
	if ((tx == 0) && (ty == 0)){
		*k = tx;
		*l = ty;
		return;
	}
	*/
	
	//let it run from 0 not 1:
	tx--, ty--;
	//00 01 02
	//10 11 12
	//20 21 22

	//printf("tx=%d ty=%d\n",tx,ty);
	//calc starting index of board->m
	start_x = (tx * (DIMENSIONS/3));
	start_y = (ty * (DIMENSIONS/3));
		
	//pick the first free square from the quadrant	
	for (i=1; i<=DIMENSIONS/3; i++)
		for (j=1; j<=DIMENSIONS/3; j++)
			if (board->m[start_x+i][start_y+j] == 0){
				*k = start_x+i;
				*l = start_y+j;
				return; //found the first one
			}
}

void possible_values(int a, int b, boardtype *board, bool possible[DIMENSIONS+1]){
	int i, j, v;
	int x, y, start_x, start_y;

	// reset possible array, all true
	possible[0] = false;
	
	for (i=1; i<=DIMENSIONS; i++)
		possible[i] = true;
	
	// rows
	for (i=1; i<=DIMENSIONS; i++){
		v = board->m[a][i];
		if (v != 0)
			possible[v] = false;
	}

	// cols
	for (i=1; i<=DIMENSIONS; i++){
		v = board->m[i][b];
		if (v != 0)
			possible[v] = false;
	}

	// quadrants
	
	// identify square a b with one of 9 quadrants (quadrants are represented as matrix 3by3 xy 
	//00 01 02
	//10 11 12
	//20 21 22
	x = (a-1) / (DIMENSIONS/3);
	y = (b-1) / (DIMENSIONS/3);
	
	start_x = (x * (DIMENSIONS/3));
	start_y = (y * (DIMENSIONS/3));
	
	for (i=1; i<=DIMENSIONS/3; i++){
		for (j=1; j<=DIMENSIONS/3; j++){
			v = board->m[start_x+i][start_y+j];
			if (v != 0)
				possible[v] = false;
		}
	}		
}

void make_move(int a[], int k, boardtype *board){
	//printf("x=%d y=%d val=%d\n",board->move[k].x, board->move[k].y, a[k]);
	fill_square(board->move[k].x, board->move[k].y, a[k], board);
}

void unmake_move(int a[], int k, boardtype *board){
	free_square(board->move[k].x, board->move[k].y, board);
}

bool is_a_solution(int a[], int k, boardtype *board){
	if (board->freecount == 0)
		return true;
	else
		return false;
}

void process_solution(int a[], int k, boardtype *board){
	print_board(board);
	finished = true;
}

// tell me which quadrant in the board has the fewest free squares
int matrix_min(int matrix[(DIMENSIONS/3)+1][(DIMENSIONS/3)+1], int *x, int *y){
	int i, j;
	int min = INT_MAX;
	
	*x = 0;
	*y = 0;
	
	for (i=1; i<=DIMENSIONS/3; i++)
		for (j=1; j<=DIMENSIONS/3; j++)
			if ((matrix[i][j] < min) && (matrix[i][j] > 0)){
				min = matrix[i][j];
				*x = i;
				*y = j;
			}
	return min;
}



void construct_candidates(int a[], int k, boardtype *board, int c[], int *ncandidates){
	int x, y;  	//position of next move
	int i; 		//counter
	bool possible[DIMENSIONS+1];  //what is possible for the 
	
	next_square(&x, &y, board);  //which square on the board shall be picked next
	//printf("next_square = %d %d\n",x,y);
	
	board->move[k].x = x;   //store our choice of next position
	board->move[k].y = y;
	
	*ncandidates = 0;
	
	if ((x<0) && (y<0)) return; //error condition, no moves possible
	
	possible_values(x, y, board, possible);
	for (i=0; i<=DIMENSIONS; i++){
		if (possible[i] == true){
			c[*ncandidates] = i;
			*ncandidates = *ncandidates + 1;
		}
	}			
}	


void backtrack(int a[], int k, boardtype *board){
	int c[MAXCANDIDATES]; //candidates for next position
	int ncandidates; // next position candidate count
	int i; //counter
	
	
	if (is_a_solution(a, k, board)){
		process_solution(a, k, board);
		//printf("found it!\n");
	}
	else{
		k = k + 1;
		//printf("k=%d\n",k);
		
		construct_candidates(a, k, board, c, &ncandidates);
		
		/*
		printf("cand: ");
		for (i=0; i<ncandidates; i++)
			printf("%d", c[i]);
		printf("\n");
		*/
		
		for (i=0; i<ncandidates; i++){
			a[k] = c[i];
			make_move(a, k, board);
			backtrack(a, k, board);
			unmake_move(a, k, board);
			if (finished) return;  // terminate early
		}
	}
	
}


void sudoku(boardtype *board){
	int solution[CELLS];
	int start = 0;
	backtrack(solution, start, board);
}


int main(void){
	
	int m, n;
	boardtype board;
	
	read_board(&board);
	sudoku(&board);
	
	
// below examples from
// http://elmo.sbs.arizona.edu/sandiway/sudoku/examples.html

	/* easy (36 filled) - done in instant
0 0 0 2 6 0 7 0 1
6 8 0 0 7 0 0 9 0
1 9 0 0 0 4 5 0 0
8 2 0 1 0 0 0 4 0
0 0 4 6 0 2 9 0 0
0 5 0 0 0 3 0 2 8
0 0 9 3 0 0 0 7 4
0 4 0 0 5 0 0 3 6
7 0 3 0 1 8 0 0 0

	//medium (24 filled) - done in 1 second
0 2 0 6 0 8 0 0 0
5 8 0 0 0 8 7 0 0
0 0 0 0 4 0 0 0 0
3 7 0 0 0 0 5 0 0
6 0 0 0 0 0 0 0 4
0 0 8 0 0 0 0 1 3
0 0 0 0 2 0 0 0 0
0 0 9 8 0 0 0 3 6
0 0 0 3 0 6 0 9 0	

	//hard (23 filled)  - done in 1 second
0 0 0 6 0 0 4 0 0
7 0 0 0 0 3 6 0 0
0 0 0 0 9 1 0 8 0
0 0 0 0 0 0 0 0 0
0 5 0 1 8 0 0 0 3
0 0 0 3 0 6 0 4 5
0 4 0 2 0 0 0 6 0
9 0 3 0 0 0 0 0 0
0 2 0 0 0 0 1 0 0

	// very hard (18 filled)  - don in 1 second
0 2 0 0 0 0 0 0 0
0 0 0 6 0 0 0 0 3
0 7 4 0 8 0 0 0 0
0 0 0 0 0 3 0 0 2
0 8 0 0 4 0 0 1 0
6 0 0 5 0 0 0 0 0
0 0 0 0 1 0 7 8 0
5 0 0 0 0 9 0 0 0
0 0 0 0 0 0 0 4 0

// apparently min is 17 filled which still has 1 solution, if less filled than no of solutions is getting bigger and MUCH bigger

	*/
 	
	
	return 0;
}