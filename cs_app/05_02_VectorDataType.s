	.file	"05_02_VectorDataType.c"
	.text
	.globl	new_vec
	.def	new_vec;	.scl	2;	.type	32;	.endef
	.seh_proc	new_vec
new_vec:
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	movq	%rcx, %rsi
	movl	$16, %ecx
	call	malloc
	movq	%rax, %rbx
	testq	%rax, %rax
	je	.L1
	movq	%rsi, (%rax)
	testq	%rsi, %rsi
	jg	.L5
	movl	$0, %esi
.L3:
	movq	%rsi, 8(%rbx)
.L1:
	movq	%rbx, %rax
	addq	$40, %rsp
	popq	%rbx
	popq	%rsi
	ret
.L5:
	movl	$8, %edx
	movq	%rsi, %rcx
	call	calloc
	movq	%rax, %rsi
	testq	%rax, %rax
	jne	.L3
	movq	%rbx, %rcx
	call	free
	movq	%rsi, %rbx
	jmp	.L1
	.seh_endproc
	.globl	get_vec_element
	.def	get_vec_element;	.scl	2;	.type	32;	.endef
	.seh_proc	get_vec_element
get_vec_element:
	.seh_endprologue
	testq	%rdx, %rdx
	js	.L8
	cmpq	%rdx, (%rcx)
	jl	.L9
	movq	8(%rcx), %rax
	movsd	(%rax,%rdx,8), %xmm0
	movsd	%xmm0, (%r8)
	movl	$1, %eax
.L6:
	ret
.L8:
	movl	$0, %eax
	jmp	.L6
.L9:
	movl	$0, %eax
	jmp	.L6
	.seh_endproc
	.globl	vec_length
	.def	vec_length;	.scl	2;	.type	32;	.endef
	.seh_proc	vec_length
vec_length:
	.seh_endprologue
	movq	(%rcx), %rax
	ret
	.seh_endproc
	.globl	get_vec_start
	.def	get_vec_start;	.scl	2;	.type	32;	.endef
	.seh_proc	get_vec_start
get_vec_start:
	.seh_endprologue
	movq	8(%rcx), %rax
	ret
	.seh_endproc
	.globl	combine1
	.def	combine1;	.scl	2;	.type	32;	.endef
	.seh_proc	combine1
combine1:
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, %rdi
	movq	%rdx, %rsi
	movq	.LC0(%rip), %rax
	movq	%rax, (%rdx)
	movl	$0, %ebx
.L13:
	movq	%rdi, %rcx
	call	vec_length
	cmpq	%rbx, %rax
	jle	.L15
	leaq	40(%rsp), %r8
	movq	%rbx, %rdx
	movq	%rdi, %rcx
	call	get_vec_element
	movsd	(%rsi), %xmm0
	mulsd	40(%rsp), %xmm0
	movsd	%xmm0, (%rsi)
	addq	$1, %rbx
	jmp	.L13
.L15:
	addq	$48, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	ret
	.seh_endproc
	.globl	combine2
	.def	combine2;	.scl	2;	.type	32;	.endef
	.seh_proc	combine2
combine2:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$56, %rsp
	.seh_stackalloc	56
	.seh_endprologue
	movq	%rcx, %rbp
	movq	%rdx, %rsi
	call	vec_length
	movq	%rax, %rdi
	movq	.LC0(%rip), %rax
	movq	%rax, (%rsi)
	movl	$0, %ebx
.L17:
	cmpq	%rdi, %rbx
	jge	.L19
	leaq	40(%rsp), %r8
	movq	%rbx, %rdx
	movq	%rbp, %rcx
	call	get_vec_element
	movsd	(%rsi), %xmm0
	mulsd	40(%rsp), %xmm0
	movsd	%xmm0, (%rsi)
	addq	$1, %rbx
	jmp	.L17
.L19:
	addq	$56, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	ret
	.seh_endproc
	.globl	combine3
	.def	combine3;	.scl	2;	.type	32;	.endef
	.seh_proc	combine3
combine3:
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, %rdi
	movq	%rdx, %rbx
	call	vec_length
	movq	%rax, %rsi
	movq	%rdi, %rcx
	call	get_vec_start
	movq	.LC0(%rip), %rdi
	movq	%rdi, (%rbx)
	movl	$0, %edx
.L21:
	cmpq	%rsi, %rdx
	jge	.L23
	movsd	(%rax,%rdx,8), %xmm0
	mulsd	(%rbx), %xmm0
	movsd	%xmm0, (%rbx)
	addq	$1, %rdx
	jmp	.L21
.L23:
	addq	$32, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	ret
	.seh_endproc
	.globl	combine4
	.def	combine4;	.scl	2;	.type	32;	.endef
	.seh_proc	combine4
combine4:
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	vec_length
	movq	%rax, %rbx
	movq	%rsi, %rcx
	call	get_vec_start
	movsd	.LC0(%rip), %xmm0
	movl	$0, %edx
.L25:
	cmpq	%rbx, %rdx
	jge	.L27
	mulsd	(%rax,%rdx,8), %xmm0
	addq	$1, %rdx
	jmp	.L25
.L27:
	movsd	%xmm0, (%rdi)
	addq	$32, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	ret
	.seh_endproc
	.globl	combine5
	.def	combine5;	.scl	2;	.type	32;	.endef
	.seh_proc	combine5
combine5:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	movq	%rcx, %rdi
	movq	%rdx, %rbp
	call	vec_length
	movq	%rax, %rsi
	leaq	-1(%rax), %rbx
	movq	%rdi, %rcx
	call	get_vec_start
	movsd	.LC0(%rip), %xmm0
	movl	$0, %edx
.L29:
	cmpq	%rbx, %rdx
	jge	.L31
	mulsd	(%rax,%rdx,8), %xmm0
	mulsd	8(%rax,%rdx,8), %xmm0
	addq	$2, %rdx
	jmp	.L29
.L32:
	mulsd	(%rax,%rdx,8), %xmm0
	addq	$1, %rdx
.L31:
	cmpq	%rsi, %rdx
	jl	.L32
	movsd	%xmm0, 0(%rbp)
	addq	$40, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	ret
	.seh_endproc
	.globl	combine5b
	.def	combine5b;	.scl	2;	.type	32;	.endef
	.seh_proc	combine5b
combine5b:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	movq	%rcx, %rdi
	movq	%rdx, %rbp
	call	vec_length
	movq	%rax, %rsi
	leaq	-4(%rax), %rbx
	movq	%rdi, %rcx
	call	get_vec_start
	movsd	.LC0(%rip), %xmm0
	movl	$0, %edx
.L34:
	cmpq	%rbx, %rdx
	jge	.L36
	mulsd	(%rax,%rdx,8), %xmm0
	mulsd	8(%rax,%rdx,8), %xmm0
	mulsd	16(%rax,%rdx,8), %xmm0
	mulsd	24(%rax,%rdx,8), %xmm0
	mulsd	32(%rax,%rdx,8), %xmm0
	addq	$5, %rdx
	jmp	.L34
.L37:
	mulsd	(%rax,%rdx,8), %xmm0
	addq	$1, %rdx
.L36:
	cmpq	%rsi, %rdx
	jl	.L37
	movsd	%xmm0, 0(%rbp)
	addq	$40, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	ret
	.seh_endproc
	.globl	combine6
	.def	combine6;	.scl	2;	.type	32;	.endef
	.seh_proc	combine6
combine6:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	movq	%rcx, %rdi
	movq	%rdx, %rbp
	call	vec_length
	movq	%rax, %rsi
	leaq	-1(%rax), %rbx
	movq	%rdi, %rcx
	call	get_vec_start
	movsd	.LC0(%rip), %xmm0
	movl	$0, %edx
.L39:
	cmpq	%rbx, %rdx
	jge	.L41
	mulsd	(%rax,%rdx,8), %xmm0
	mulsd	8(%rax,%rdx,8), %xmm0
	addq	$2, %rdx
	jmp	.L39
.L42:
	mulsd	(%rax,%rdx,8), %xmm0
	addq	$1, %rdx
.L41:
	cmpq	%rsi, %rdx
	jl	.L42
	movsd	%xmm0, 0(%rbp)
	addq	$40, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	call	__main
	movl	$0, %eax
	addq	$40, %rsp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC0:
	.long	0
	.long	1072693248
	.ident	"GCC: (GNU) 9.3.0"
	.def	malloc;	.scl	2;	.type	32;	.endef
	.def	calloc;	.scl	2;	.type	32;	.endef
	.def	free;	.scl	2;	.type	32;	.endef
