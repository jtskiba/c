#include <stdio.h>
#include <stdlib.h>

//p.259 PP3.28

/* This code reverses the bits in x, creating a mirror image. It does this by
shifting the bits of x from left to right, and then filling these bits in as it
shifts val from right to left.
*/

long fun_b(unsigned int x){
	long val = 0;
	long i;
	for (i=64; i != 0; i--){
		val = (val<<1) | (x & 0x1);
		x>>=1;
	}
	return val;
}


int main(void){
	long t=0x1; 
	//expecting mirror: t=0000 0000 0000 0000 0000 0000 0000 0001 (1 in two's signed) to mirror=1000 0000 0000 0000 0000 0000 0000 0000 
	//(--9223372036854775808 in two's signed)
	printf("sizeof t = %d\n",sizeof(t)); //expecting 8
	printf("mirror of %ld is %ld\n",t,fun_b(t));
	
}

/*
fun_b:
	movl	$64, %edx
	movl	$0, %eax
	jmp	.L2
.L3:
	addq	%rax, %rax
	movl	%ecx, %r8d
	andl	$1, %r8d
	orq	%r8, %rax
	shrl	%ecx
	subq	$1, %rdx
.L2:
	testq	%rdx, %rdx
	jne	.L3
	ret
*/