	.file	"03_05_Remdiv.c"
	.text
	.globl	remdiv
	.def	remdiv;	.scl	2;	.type	32;	.endef
	.seh_proc	remdiv
remdiv:
	.seh_endprologue
	movq	%rcx, %rax
	movq	%rdx, %r10
	cqto
	idivq	%r10
	movq	%rax, (%r8)
	movq	%rdx, (%r9)
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 9.3.0"
