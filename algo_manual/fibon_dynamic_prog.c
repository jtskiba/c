
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXN 45
#define UNKNOWN -1

long f[MAXN+1];
clock_t start, end;
double cpu_time_used;


/* Skiena section 8.1 Dynamic programming - basic example using Fibonacci
*/

double time_it(long fn){
	clock_t s, e;
	long o;
	s = clock();
	o = fn;
	e = clock();
	return( ((double) (end - start)) ); // / CLOCKS_PER_SEC;
}

// recursive.. takes longest
long fib_r(int n){
	if (n==0) return(0);
	if (n==1) return(1);
	return (fib_r(n-2)+fib_r(n-1));
}

// by cashing - looking up results already calculated
long fib_c(int n){
	if (f[n] == UNKNOWN)
		return (fib_r(n-2)+fib_r(n-1));
	else
		return (f[n]);
}
long fib_c_driver(int n){
	int i;
	f[0]=0;
	f[1]=1;
	for (i=2;i<=n;i++) f[i] = UNKNOWN;
	return (fib_c(n));
}

// by dynamic programming
long fib_dp(int n){
	int i;
	long f[MAXN+1];
	
	f[0]=0;
	f[1]=1;
	for (i=2;i<=n;i++) f[i]=f[i-2]+f[i-1];
	return(f[n]);
}

// by dyn programming with minimal storage needs (ultimate)
long fib_ultimate(int n){
	int i;
	long back_1 = 1, back_2 = 0;
	long new;
		
	if (n==0) return(0);
	if (n==1) return(1);
	
	for (i=2; i<n; i++){
		new = back_2 + back_1;
		back_2 = back_1;
		back_1 = new;
	}		
	return(back_2 + back_1);
}

int main(void){
	int m = 45;
	long out;
	
	/* below two take about 7 seconds for m = 45, the third dp is instant so i increase m
	
	// recursive (takes about 7sec
	start = clock();
	out = fib_r(m);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("fib of %d recursive: %d (time taken: %f)\n",m,out,cpu_time_used);
	
	// cashing
	start = clock();
	out = fib_c_driver(m);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("fib of %d cashing: %d (time taken: %f)\n",m,out,cpu_time_used);
	*/
	
	
	// dynamic programming (same as cashing but doing ops in order f1, f2, f3 rather then as emerging during computation done in cashing example
	start = clock();
	out = fib_dp(m);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("fib of %d dyn progr: %d (time taken: %f)\n",m,out,cpu_time_used);

    // ultimate - dynamic programming with minimal storage req needed
	start = clock();
	out = fib_ultimate(m);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("fib of %d dpr ultim: %d (time taken: %f)\n",m,out,cpu_time_used);

}
