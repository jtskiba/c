	.file	"03_06_Uremdiv.c"
	.text
	.globl	uremdiv
	.def	uremdiv;	.scl	2;	.type	32;	.endef
	.seh_proc	uremdiv
uremdiv:
	.seh_endprologue
	movq	%rcx, %rax
	movq	%rdx, %r10
	movl	$0, %edx
	divq	%r10
	movq	%rax, (%r8)
	movq	%rdx, (%r9)
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 9.3.0"
