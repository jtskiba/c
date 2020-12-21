#include <stdio.h>

__asm__( 
	"	.text\n\t"
	"	.globl	pushtest\n\t"
	"pushtest:\n\t"
		"movq	%rsp, %rax\n\t"
		"pushq	%rsp\n\t"
		"popq	%rdx\n\t"
		"subq	%rdx, %rax\n\t"
	//	"addq 	$1, %rax\n\t"
		"ret"
	);

int main(void){
	printf("result: %d",pushtest());
}
