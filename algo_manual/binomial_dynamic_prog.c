#include <stdio.h>
#include <string.h>

#define MAXN 45


/* Skiena section 8.1.4 Dynamic programming - Binomial coefficients
*/


int binomial_coefficients(int n, int m){
	int bc[MAXN+1][MAXN+1];
	int i,j;
	
	for(i=0;i<=n;i++) bc[i][0]=1;
	for(i=0;i<=n;i++) bc[i][i]=1;
	
	for (i=1;i<=n;i++)
		for (j=1;j<i;j++)
			bc[i][j] = bc[i-1][j-1] + bc[i-1][j];
	return(bc[n][m]);
}


int main(void){
	int n = 4, m = 2;
	int out;
	
	out = binomial_coefficients(n,m);
	printf("bin coeff n=%d m=%d: %d \n",n,m,out);
}
