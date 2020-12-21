	.file	"03_10_MirrorBits.c"
	.text
	.globl	fun_b
	.def	fun_b;	.scl	2;	.type	32;	.endef
	.seh_proc	fun_b
fun_b:
	.seh_endprologue
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
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "sizeof t = %d\12\0"
.LC1:
	.ascii "mirror of %ld is %ld\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	call	__main
	movl	$8, %edx
	leaq	.LC0(%rip), %rcx
	call	printf
	movl	$1, %ecx
	call	fun_b
	movq	%rax, %r8
	movl	$1, %edx
	leaq	.LC1(%rip), %rcx
	call	printf
	movl	$0, %eax
	addq	$40, %rsp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 9.3.0"
	.def	printf;	.scl	2;	.type	32;	.endef
