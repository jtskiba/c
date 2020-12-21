	.file	"03_03_SimpleExample.c"
	.text
	.globl	simple
	.def	simple;	.scl	2;	.type	32;	.endef
	.seh_proc	simple
simple:
	.seh_endprologue
	movl	%edx, %eax
	addl	(%rcx), %eax
	movl	%eax, (%rcx)
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 9.3.0"
