	.text
	.file	"hello.bc"
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rax
.Ltmp0:
	.cfi_def_cfa_offset 16
	movl	$.Lstr, %edi
	callq	puts
	movl	$.Lstr, %edi
	callq	puts
	movl	$.Lstr, %edi
	callq	puts
	movl	$.Lstr, %edi
	callq	puts
	movl	$.Lstr, %edi
	callq	puts
	movl	$.Lstr, %edi
	callq	puts
	movl	$.Lstr, %edi
	callq	puts
	movl	$.Lstr, %edi
	callq	puts
	movl	$.Lstr, %edi
	callq	puts
	movl	$.Lstr, %edi
	callq	puts
	xorl	%eax, %eax
	popq	%rdx
	retq
.Ltmp1:
	.size	main, .Ltmp1-main
	.cfi_endproc

	.type	.Lstr,@object           # @str
	.section	.rodata.str1.16,"aMS",@progbits,1
	.align	16
.Lstr:
	.asciz	"(le suicide oui mais avec le sourire)"
	.size	.Lstr, 38


	.ident	"clang version 3.5.0 (tags/RELEASE_350/final)"
	.section	".note.GNU-stack","",@progbits
