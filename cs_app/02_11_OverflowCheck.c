#include <stdio.h>
#include <string.h>
#include <limits.h>

void print_array(int a[], int cnt){
	int i;
	for (i=0;i<cnt;i++)
		printf("%d ",a[i]);
	printf("\n");
}

/* Determine whether string s is longer than string t */
/* WARNING: This function is buggy */
int uadd_ok(unsigned x, unsigned y) {
	unsigned int sum = x + y;
	if (sum<x) return 1; else return 0; //or sum<y would also do
} 

/* Determine whether arguments can be added without overflow */
int tadd_ok(int x, int y){
	int sum = x + y;
	if (((sum < 0) && (x>0) && (y>0)) || 
		((sum > 0) && (x<0) && (y<0)))
		return 0;
	else
		return 1;
}

/* Determine whether arguments can be subtracted without overflow */
/* WARNING: This code is buggy. */
/* JS: it will not work work x=0 and y=INT_MIN, tried below */
int tsub_ok(int x, int y) {
	return tadd_ok(x, -y);
}

// my version

//my version
int tsub_ok2(int x, int y){
	int sub = x - y;
	printf(">> x=%d, y=%d, sum=%d\n", x, y, sum);
	if (((sub < 0) && (x>=0) && (y<0)) ||
		((sub < 0) && (x>0)  && (y<=0))||	
		((sub > 0) && (x<=0) && (y>0)) || 
		((sub > 0) && (x<0)  && (y>=0)))
		return 0;
	else
		return 1;
}

/* Determine whether arguments can be multiplied without overflow */
int tmult_ok(int x, int y) {
	int p = x*y;
	/* Either x is zero, or dividing p by x gives y */
	return !x || p/x == y;
}


int main(void){
			
	/*		
	//////////////////////////////////////////////////////////
	//// Chapter 2 Representing and Manipulating Information 
	//////////////////////////////////////////////////////////
	*/
	
	/*p.81 PP2.27*/
	
	// UINT_MAX is equal to 4294967295 (my machine)
	
	unsigned int a = UINT_MAX-1;
	unsigned int b = 1; //should cause no overflow, resulting in UINT_MAX
	unsigned int c = 2; //addition with a should cause overflow, resuling in 0
	printf("%d\n",uadd_ok(a,b));
	printf("%d\n\n",uadd_ok(a,c));
	
	/*p.86 PP2.30*/
	int m = INT_MIN+1;
	//printf("m=%d, m-2=%d\n",m,m-2);
	int n = INT_MAX-1; 
	//printf("n=%d, n+2=%d\n",n,n+2);
	
	printf("neg overflow = %d\n",tadd_ok(m,-2)); //case 1 => expecting 0
	printf("normal = %d\n",tadd_ok(m,-1)); //case 2 => expecting 1
	printf("normal = %d\n",tadd_ok(n,1)); //case 3 => expecting 1
	printf("pos overflow = %d\n\n",tadd_ok(n,2)); //case 4 => expecting 0
	
	//p.87 PP2.32
	m = 0;
	n = INT_MIN;
	printf("bug shown (expecting overflow so 0 result):%d\n",tsub_ok(m,n));
	printf("corrected shown (expecting overflow so 0 result):%d\n",tsub_ok2(m,n));
	printf("more ex (expecting overflow so 0 result):%d\n\n",tsub_ok2(INT_MIN,1));
	
	//p.90 PP2.35
	
	
	
	return 0;
}