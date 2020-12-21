#include <stdio.h>

int poptest(void);

__asm__( 
	//"	.text\n\t"
	//"	.globl	poptest\n\t"
	"poptest:\n\t"
		"movq	%rsp, %rdi\n\t"
		"pushq	$0xabcd\n\t"
		"popq	%rsp\n\t"
		"movq	%rsp, %rax\n\t"
		"movq 	%rdi, %rsp\n\t"
		"ret"
	);

int main(void){
	printf("result: %x", poptest());
}
