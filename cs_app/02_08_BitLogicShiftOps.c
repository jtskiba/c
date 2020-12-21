#include <stdio.h>

void print_array(int a[], int cnt){
	int i;
	for (i=0;i<cnt;i++)
		printf("%d ",a[i]);
	printf("\n");
}

int bis(int x, int m){
	return (x | m);
}

int bic(int x, int m){
	return (x & (~m));
}

int bool_or(int x, int y){
	return bis(x,y);
}

int bool_xor(int x, int y){
	return bis(bic(x,y),bic(y,x));
}

int main(void){
			
	/*		
	//////////////////////////////////////////////////////////
	//// Chapter 2 Representing and Manipulating Information 
	//////////////////////////////////////////////////////////
	*/
	
	/*p.53 PP2.14*/
	int x;
	int y;
	x = 0x66; /* this is 0110 0110 */
	y = 0x39; /* this is 0011 1001 */
	printf("x=0x66 or 0110 0110\ny=0x39 or 0011 1001\n");
	printf("x&y=%x (expected 0x20 or 0010 0000)\n",x&y);
	printf("x|y=%x (expected 0x7F or 0111 1111)\n",x|y);
	printf("~x|~y=%x (expected 0xDF or 1101 1111 !! agreed, there is lots of Fs before)\n",(~x)|(~y));
	printf("x&!y=%x (expected x&false ie 0x00 !! careful ! is not ~)\n",x&(!y));
	printf("x&&y=%x (expected true&&true=true ie 0x01)\n)",x&&y);
	printf("x||y=%x (expected true||true=true ie 0x01)\n)",x||y);
	printf("!x||!y=%x (expected false||false=false ie 0x00)\n",(!x)||(!y));
	printf("x&&(~y)=%x (expected true&&true=true ie 0x01)\n\n",(x)&&(~y));
	
	/*PP2.15 p.53*/
	x = 23;
	y = 12;
	printf("x=%d, y=%d\n",x,y);
	printf("x==y is equivalent to !bic or !(x & (~y))\nx==y: %d\n",x==y);
	printf("!(x&~y):%d\n\n",!(x & (~y)));

	x = 21;
	y = 21;
	printf("x=%d, y=%d\n",x,y);
	printf("x==y: %d\n",x==y);
	printf("!(x&~y):%d\n\n",!(x & (~y)));

	/*
	//Shifting by k, for large k (effective k mod m)
	// in GNU gcc it is not allowed and warning is thrown out!
	// checked other stds (listed below) but none seem to accept the below
	*/
	
	/* commented out as it throws out warnings
	int ival 		= 0xFEDCBA89 << 32;
	int aval 		= 0xFEDCBA89 >> 36;
	unsigned uval 	= 0xFEDCBA89 >> 40;
	
	printf("i=%x\n",ival);
	printf("a=%x\n",aval);
	printf("u=%x\n\n",uval);
	*/
	
	/*
	GNU 89 none, -std=gnu89
	ANSI, ISO C90 -ansi, -std=c89
	ISO C99 -std=c99
	GNU 99 -std=gnu99
	*/
	
	//PP2.16 p.56
	char xx = 0xC3;
	printf("<<3: %x\n",xx<<3);
	printf(">>2(arith):%x\n",xx>>2);
	unsigned int ux = 0xC3;
	printf(">>2(log):%x\n\n",ux>>2);
	
	//PP2.17 p.61
	// short is 2-byte size so 16-bits
	unsigned short m=0x800F; // or 1000 0000 0000 1111 = 2^15 + 2^3 + 2^2 + 2^1 + 2^0 = 32,768 + 8 + 4 + 2 + 1 = 32,783 decimal
	short int n=0x800F;	 // or 1000 0000 0000 1111 =-2^15 + 2^3 + 2^2 + 2^1 + 2^0 = 32,768 + 8 + 4 + 2 + 1 =-32,753 decimal
	printf("m = %d\n", m);
	printf("n = %d\n\n", n);
	
	uint8_t d = 0x8F; // or 1000 1111 = 2^7 + 2^3 + 2^2 + 2^1 + 2^0 = 128 + 8 + 4 + 2 + 1 = 143 decimal
	int8_t e = 0x8F;  // or 1000 1111 =-2^7 + 2^3 + 2^2 + 2^1 + 2^0 = 128 + 8 + 4 + 2 + 1 =-113 decimal
	printf("d = %d\n", d);
	printf("e = %d\n\n", e);
	
	//PP2.21 p.71
	printf("-2147483647-1 == 2147483648U result is %d\n",-2147483647-1 == 2147483648U); 
	//exp true as left side is signed -2147483648 which needs to be  cast to unsigned (as rhs is unsigned) which translates 
	//   to 2^32 - 2147483648 and is eq 2147483648
	printf("-2147483647-1 < 2147483647 result is %d\n",-2147483647-1 < 2147483647);
	printf("-2147483647-1U < 2147483647 result is %d\n",-2147483647-1U < 2147483647);
	// need to cast all signed to unsigned t=-2147483647 => t+2^32= 2,147,483,649
	//       							   t= 2147483647 => t+2^32= 6,442,450,943 mod 4,294,967,296 (i.e. 2^32) = 2,147,483,647
	//								hence 2,147,483,649 - 1 < 2,147,483,647  => false 0
	printf("-2147483647-1 == 2147483648U result is %d\n",-2147483647-1 == 2147483648U); 
	

	
	
	return 0;
}