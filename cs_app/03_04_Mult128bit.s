	.file	"03_04_Mult128bit.c"
	.text
	.globl	store_uprod
	.def	store_uprod;	.scl	2;	.type	32;	.endef
	.seh_proc	store_uprod
store_uprod:
	.seh_endprologue
	movq	%rdx, %rax
	mulq	%r8
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 9.3.0"
