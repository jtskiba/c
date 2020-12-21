#include <stdio.h>
#include <stdlib.h>

// regular matrix multiplication in O(n^3), i.e. A(i,k).B(k,j)= C(i,j)
void matrix_mult(int i, int j, int k, int A[i][k], int B[k][j], int C[i][j]){
	int x,y,z;
	
	for (x=0; x<i; x++){
		for (y=0; y<j; y++){
			C[x][y] = 0;
			for (z=0; z<k; z++){
				C[x][y] = C[x][y] + (A[x][z] * B[z][y]);
			}
		}
	}	
}

void print_matrix(int i, int j, int M[i][j]){
	int x,y;
		
	for (x=0; x<i; x++){
		for (y=0; y<j; y++){
			printf("%4d",M[x][y]);
		}
		printf("\n");
	}
}

int main(void){
	int cols_A, cols_B, cols_C, rows_A, rows_B, rows_C;
	int i, j; /*for iterations*/ 
	int A[3][5] = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}}; //A[rows][columns]
	int B[5][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
	int C[3][3];
	
	// sizeof(A)     3*5*intsize4 = 60
	// sizeof(A[0])    5*intsize4 = 20
	// sizeof(int)       intsize4 =  4
	
	/*
	printf("%d\n",sizeof(A)/sizeof(A[0])); //# rows = 3
	printf("%d\n",sizeof(B)/sizeof(B[0])); //# rows = 5
	
	printf("%d\n",sizeof(A[0])/sizeof(int)); //# cols = 5
	printf("%d\n",sizeof(B[0])/sizeof(int)); //# cols = 3
	*/
	
	cols_A = sizeof(A[0])/sizeof(int); //k
	cols_B = sizeof(B[0])/sizeof(int); //j
	rows_A = sizeof(A)   /sizeof(A[0]);//i
	rows_B = sizeof(B)   /sizeof(B[0]);//k
		
	
	matrix_mult(rows_A,cols_B,rows_B,A,B,C);
	
	rows_C = sizeof(C)   /sizeof(C[0]);
	cols_C = sizeof(C[0])/sizeof(int);
	print_matrix(rows_C, cols_C, C);
	// A.B = C
	// [15 30 45]
	// [15 30 45]
	// [15 30 45]
		
	return 0;
}

