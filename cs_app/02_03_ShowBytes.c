#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len){
	int i;
	for (i=0; i < len; i++)
		printf(" %.2x", start[i]);
	printf("\n");
}

void show_int(int x){
	show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x){
	show_bytes((byte_pointer) &x, sizeof(float));
}

void show_double(double x){
	show_bytes((byte_pointer) &x, sizeof(double));
}

void show_pointer(void *x){
	show_bytes((byte_pointer) &x, sizeof(void *));
}

void test_show_bytes(int val){
	int ival = val;
	float fval = (float) val;
	double dval = (double) val;
	int *pval = &ival;
	
	show_int(ival);
	show_float(fval);
	show_double(dval);
	show_pointer(pval);
}

int sum(int x, int y){
	return x + y;
}


int main(void){
	
		
	//////////////////////////////////////////////////////////
	//// Chapter 2 Representing and Manipulating Information 
	//////////////////////////////////////////////////////////
	
		
	//p.42
	
	/*
	int a = 270;
	float b = 2.0;
	long *p;
	*p = 1;
	
	show_int(a);
	show_float(b);
	show_pointer(p);
	*/
	int x;
	test_show_bytes(x = 12345);
	
	// practice problem 2.5 on p.45
	// i am running Intel machine, so a little-endian result expected
	// i.e A=21, B=A 43, C=A B 65
	// for big-endian expetation would be A=87, B=A 65, C=A B 43
	int i = 0x87654321;
	byte_pointer ip = (byte_pointer) &i;
	show_bytes(ip,1);
	show_bytes(ip,2);
	show_bytes(ip,3);
	printf("\n");
	
	//string rep
	char *str = "12345";
	show_bytes(str,6);
	printf("\n");
	
	// PrProb 2.7
	str = "abcdef";
	show_bytes(str,7);
	printf("\n");
	
	
	
	
	return 0;
}