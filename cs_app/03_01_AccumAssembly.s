	.file	"03_01_AccumAssembly.c"
	.intel_syntax noprefix
	.text
	.globl	sum
	.def	sum;	.scl	2;	.type	32;	.endef
	.seh_proc	sum
sum:
	.seh_endprologue
	lea	eax, [rcx+rdx]
	add	DWORD PTR accum[rip], eax
	ret
	.seh_endproc
	.globl	accum
	.bss
	.align 4
accum:
	.space 4
	.ident	"GCC: (GNU) 9.3.0"
