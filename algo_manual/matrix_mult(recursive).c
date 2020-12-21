#include <stdio.h>
#include <stdlib.h>


/*regular matrix multiplication in O(n^3), i.e. A(i,k).B(k,j)= C(i,j)
void matrix_mult(int i, int j, int k, int from, int A[i][k], int B[k][j], int C[i][j]){
	int x,y,z;
	
	for (x=from+0; x<from+i; x++){
		for (y=from+0; y<from+j; y++){
			C[x][y] = 0;
			for (z=from+0; z<from+k; z++){
				C[x][y] = C[x][y] + (A[x][z] * B[z][y]);
			}
		}
	}	
}

void multm(int s, int ss, int fr_Ar, int fr_Ac, int fr_Br, int fr_Bc, int fr_Cr, int fr_Cc, int A[s][s], int B[s][s], int C[s][s]){
	int i, j, k;
	int subtotal;
		
	for (i = 0; i < ss; i++){
		for (j = 0; j < ss; j++){
			subtotal = 0;
			for (k = 0; k < ss; k++){
				subtotal = subtotal + (A[fr_Ar + i][fr_Ac + k] * B[fr_Br + k][fr_Bc + j]);
			}
			C[fr_Cr + i][fr_Cc + j] += subtotal;
		}
	}
}

void addm(int s, int ss, int fr_Ar, int fr_Ac, int fr_Br, int fr_Bc, int fr_Cr, int fr_Cc, int A[s][s], int B[s][s], int C[s][s]){
	int i, j, k;
	
	for (i = 0; i < ss; i++){
		for (j = 0; j < ss; j++){
			C[fr_Cr + i][fr_Cc + j] = A[fr_Ar + i][fr_Ac + j] + B[fr_Br + i][fr_Bc + j];
		}
	}
}


//size = s; subsize = ss (i.e. overall matrix is 4x4 so s= 4 but i want to deal with its 2x2 part so ss =2
//from_A_row, from_A_column	
void printm(int s, int ss, int fr_Ar, int fr_Ac, int M[s][s]){ 

	int i, j;
		
	for (i = 0; i < ss; i++){
		for (j = 0; j < ss; j++){
			printf("%4d", M[fr_Ar + i][fr_Ac + j]);			
		}
		printf("\n");
	}
}
*/
void msplit(int size, int flag, int A[size][size], int A1[size/2][size/2], int A2[size/2][size/2], int A3[size/2][size/2], int A4[size/2][size/2]){
//splits (flag=) matrices as shown below in the commennts from A into 4 quadrants A1 A2 | A3 A4; or if flag =1 other way round
	// flag = 0 for split, flag = 1 for combine
	int i, j, k, half, map;
	half = (size * size)/2;
	j = 0, k = 0;
	for(i=0; i < half; i++){
		map = ((i / (size/2)) % 2); // e.g. translates index of A 4x4 into indexes of 4 matrices 2x2 such that A = a1 a2 
																												 //a3 a4
		if (map == 0) { 
			if (flag == 0){
				A1[j/(size/2)][j%(size/2)] = A[i/size][i%size];
				j++;
			}
			else {
				A[i/size][i%size] = A1[j/(size/2)][j%(size/2)];
				j++;
			}
		}
		else if (map == 1) {
			if (flag == 0){
				A2[k/(size/2)][k%(size/2)] = A[i/size][i%size];
				k++;
			}
			else {
				A[i/size][i%size] = A2[k/(size/2)][k%(size/2)];
				k++;
			}
		}
		else
			printf("error\n");
	}
	j = 0, k = 0;
	for(i=half; i < (2 * half); i++){
		map = ((i / (size/2)) % 2);
		if (map == 0) { 
			if (flag == 0){
				A3[j/(size/2)][j%(size/2)] = A[i/size][i%size];
				j++;
			}
			else{
				A[i/size][i%size] = A3[j/(size/2)][j%(size/2)];
				j++;
			}
		}
		else if (map == 1) {
			if (flag == 0){
				A4[k/(size/2)][k%(size/2)] = A[i/size][i%size];
				k++;
			}
			else {
				A[i/size][i%size] = A4[k/(size/2)][k%(size/2)];
				k++;
			}
		}
		else
			printf("error\n");
	}
	
}


void madd(int size, int A[size][size], int B[size][size], int C[size][size]){ 
	int i, j;
		
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			C[i][j] = A[i][j] + B[i][j];  			
		}
	}
}

void mmult(int size, int A[size][size], int B[size][size], int C[size][size]){ 
	int i, j, k;
	
	int A1[size/2][size/2], A2[size/2][size/2], A3[size/2][size/2], A4[size/2][size/2];
	int B1[size/2][size/2], B2[size/2][size/2], B3[size/2][size/2], B4[size/2][size/2];
	int C1[size/2][size/2], C2[size/2][size/2], C3[size/2][size/2], C4[size/2][size/2];
	int Temp1[size/2][size/2], Temp2[size/2][size/2];
	
	if (size == 2){
		for (i = 0; i < size; i++){
			for (j = 0; j < size; j++){
				C[i][j] = 0;
				for (k = 0; k < size; k++){
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}
	}
	else if (size > 2) {
		msplit(size, 0, A, A1, A2, A3, A4);
		msplit(size, 0, B, B1, B2, B3, B4);
		mmult(size/2, A1, B1, Temp1), mmult(size/2, A2, B3, Temp2), madd(size/2, Temp1, Temp2, C1);
		mmult(size/2, A1, B2, Temp1), mmult(size/2, A2, B4, Temp2), madd(size/2, Temp1, Temp2, C2);
		mmult(size/2, A3, B1, Temp1), mmult(size/2, A4, B3, Temp2), madd(size/2, Temp1, Temp2, C3);
		mmult(size/2, A3, B2, Temp1), mmult(size/2, A4, B4, Temp2), madd(size/2, Temp1, Temp2, C4);
		msplit(size, 1, C, C1, C2, C3, C4);
	}
	else {
		printf("Error - size of matrix not 2^n"); //fudge really, just to flag sth went wrong
	}
}

void mprint(int size, int M[size][size]){ 
	int i, j;
		
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			printf("%4d", M[i][j]);			
		}
		printf("\n");
	}
	printf("\n");
}

int main(void){
	int cols_A, cols_B, cols_C, rows_A, rows_B, rows_C;
	int i, j; /*for iterations*/ 

	int A[3][5] = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}}; //A[rows][columns]
	int B[5][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
	int C[3][3];
	
	int D1[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	int D2[4][4] = {{1, 0, 0, 1}, {1, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 1}};
	int D3[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
	int D3_1[2][2];
	int D3_2[2][2];
	int D3_3[2][2];
	int D3_4[2][2];
	int D4[4][4];
	
	
	
	
	
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
		
	//matrix_mult(rows_A,cols_B,rows_B, 0, A,B,C);
	
	rows_C = sizeof(C)   /sizeof(C[0]);
	cols_C = sizeof(C[0])/sizeof(int);
	
	//print_matrix(rows_C, cols_C, 0, &C[0][0]);
	
	// A.B = C
	// [15 30 45]
	// [15 30 45]
	// [15 30 45]
	//printf("\n");
	//matrix_add(3, D1, D2, C);
	//print_matrix(3, 3, 0, &C[0][0]);
	//print_matrix(2, 2, 1, &C[1][1]); 
	
	/*
	printm(4, 4, 0, 0, D1);
	printf("\n");
	
	addm(4, 2, 0, 0, 1, 1, 2, 0, D1, D1, D3);
	printm(4, 4, 0, 0, D3);
	printf("\n");
	
	multm(4, 2, 0, 0, 1, 1, 0, 2, D1, D1, D3);
	printm(4, 4, 0, 0, D3);
	printf("\n");
	*/
	
	madd(4, D1, D2, D3);
	mprint(4, D3);
	msplit(4, 0, D3, D3_1, D3_2, D3_3, D3_4);
	
	mprint(2, D3_1);
	mprint(2, D3_2);
	mprint(2, D3_3);
	mprint(2, D3_4);
	
	msplit(4, 1, D4, D3_1, D3_2, D3_3, D3_4);
	mprint(4, D4);
	
	// showing how multiplication works...
	mmult(4, D1, D2, D4);
	mprint(4, D1);
	mprint(4, D2);
	mprint(4, D4);
	// done!
	
	return 0;
}

