	.file	"traps.c"
	.text
	.type	get_current, @function
get_current:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	$-4096, %rax
#APP
# 57 "../include/processor.h" 1
	andl %esp,%rax;
# 0 "" 2
#NO_APP
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	get_current, .-get_current
	.globl	jiffies
	.bss
	.align 8
	.type	jiffies, @object
	.size	jiffies, 8
jiffies:
	.zero	8
	.section	.rodata
.LC0:
	.string	"do_double_fault\n"
	.text
	.globl	do_double_fault
	.type	do_double_fault, @function
do_double_fault:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	do_double_fault, .-do_double_fault
	.section	.rodata
.LC1:
	.string	"do_general_protection\n"
	.text
	.globl	do_general_protection
	.type	do_general_protection, @function
do_general_protection:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	do_general_protection, .-do_general_protection
	.section	.rodata
.LC2:
	.string	"do_divide_error\n"
	.text
	.globl	do_divide_error
	.type	do_divide_error, @function
do_divide_error:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	do_divide_error, .-do_divide_error
	.section	.rodata
.LC3:
	.string	"do_int3\n"
	.text
	.globl	do_int3
	.type	do_int3, @function
do_int3:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	do_int3, .-do_int3
	.section	.rodata
.LC4:
	.string	"do_nmi\n"
	.text
	.globl	do_nmi
	.type	do_nmi, @function
do_nmi:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	do_nmi, .-do_nmi
	.section	.rodata
.LC5:
	.string	"do_debug\n"
	.text
	.globl	do_debug
	.type	do_debug, @function
do_debug:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC5(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	do_debug, .-do_debug
	.section	.rodata
.LC6:
	.string	"do_overflow\n"
	.text
	.globl	do_overflow
	.type	do_overflow, @function
do_overflow:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC6(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	do_overflow, .-do_overflow
	.section	.rodata
.LC7:
	.string	"do_bounds\n"
	.text
	.globl	do_bounds
	.type	do_bounds, @function
do_bounds:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC7(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	do_bounds, .-do_bounds
	.section	.rodata
.LC8:
	.string	"do_invalid_op\n"
	.text
	.globl	do_invalid_op
	.type	do_invalid_op, @function
do_invalid_op:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC8(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	do_invalid_op, .-do_invalid_op
	.section	.rodata
.LC9:
	.string	"do_device_not_available\n"
	.text
	.globl	do_device_not_available
	.type	do_device_not_available, @function
do_device_not_available:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC9(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	do_device_not_available, .-do_device_not_available
	.section	.rodata
	.align 8
.LC10:
	.string	"do_coprocessor_segment_overrun\n"
	.text
	.globl	do_coprocessor_segment_overrun
	.type	do_coprocessor_segment_overrun, @function
do_coprocessor_segment_overrun:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC10(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	do_coprocessor_segment_overrun, .-do_coprocessor_segment_overrun
	.section	.rodata
.LC11:
	.string	"do_invalid_TSS\n"
	.text
	.globl	do_invalid_TSS
	.type	do_invalid_TSS, @function
do_invalid_TSS:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC11(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	do_invalid_TSS, .-do_invalid_TSS
	.section	.rodata
.LC12:
	.string	"do_segment_not_present\n"
	.text
	.globl	do_segment_not_present
	.type	do_segment_not_present, @function
do_segment_not_present:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC12(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	do_segment_not_present, .-do_segment_not_present
	.section	.rodata
.LC13:
	.string	"do_stack_segment\n"
	.text
	.globl	do_stack_segment
	.type	do_stack_segment, @function
do_stack_segment:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC13(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	do_stack_segment, .-do_stack_segment
	.section	.rodata
.LC14:
	.string	"do_coprocessor_error\n"
	.text
	.globl	do_coprocessor_error
	.type	do_coprocessor_error, @function
do_coprocessor_error:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC14(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	do_coprocessor_error, .-do_coprocessor_error
	.section	.rodata
.LC15:
	.string	"do_reserved\n"
	.text
	.globl	do_reserved
	.type	do_reserved, @function
do_reserved:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC15(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	do_reserved, .-do_reserved
	.section	.rodata
.LC16:
	.string	"%d, %d "
	.text
	.globl	switch_to
	.type	switch_to, @function
switch_to:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	cmpq	-16(%rbp), %rax
	je	.L22
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC16(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movq	-16(%rbp), %rdx
	addq	$8, %rdx
#APP
# 87 "traps.c" 1
	 pushf 	
push %ebp 	
push $9f	
mov %esp,(%eax)	
mov (%edx),%esp 	
ret9: 	
pop %ebp 	
popf 	

# 0 "" 2
#NO_APP
	jmp	.L19
.L22:
	nop
.L19:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	switch_to, .-switch_to
	.globl	do_timer
	.type	do_timer, @function
do_timer:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, -12(%rbp)
	jmp	.L24
.L27:
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	task(%rip), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L25
	movq	-8(%rbp), %rax
	movq	88(%rax), %rax
	testq	%rax, %rax
	je	.L25
	call	get_current
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	switch_to
	jmp	.L26
.L25:
	addl	$1, -12(%rbp)
.L24:
	cmpl	$9, -12(%rbp)
	jle	.L27
.L26:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	do_timer, .-do_timer
	.section	.rodata
.LC17:
	.string	"system call %d \n"
	.text
	.globl	do_sys_call
	.type	do_sys_call, @function
do_sys_call:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC17(%rip), %rdi
	movl	$0, %eax
	call	printk@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	do_sys_call, .-do_sys_call
	.globl	set_gate
	.type	set_gate, @function
set_gate:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, -40(%rbp)
	movl	%ecx, -52(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movl	-52(%rbp), %eax
	sall	$13, %eax
	movl	%eax, %edx
	movl	-40(%rbp), %eax
	sall	$8, %eax
	addl	%edx, %eax
	addw	$-32768, %ax
	movw	%ax, -26(%rbp)
	movl	-36(%rbp), %ecx
	movq	-48(%rbp), %rax
#APP
# 115 "traps.c" 1
	    shl $3, %ecx	
mov $0x10,%bx 	
mov %bx,%ds 	
mov $0x90000,%ebx 	
mov $0x080000,%edx 	
mov %ax,%dx 	
mov -26(%rbp),%ax 	
add %ecx,%ebx 	
mov %edx,(%ebx) 	
add $0x4 , %ebx 	
mov %eax,(%ebx) 	

# 0 "" 2
#NO_APP
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L30
	call	__stack_chk_fail@PLT
.L30:
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	set_gate, .-set_gate
	.globl	set_trap_gate
	.type	set_trap_gate, @function
set_trap_gate:
.LFB21:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rsi
	movl	-4(%rbp), %eax
	movl	$0, %ecx
	movl	$15, %edx
	movl	%eax, %edi
	call	set_gate
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	set_trap_gate, .-set_trap_gate
	.globl	set_intr_gate
	.type	set_intr_gate, @function
set_intr_gate:
.LFB22:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rsi
	movl	-4(%rbp), %eax
	movl	$0, %ecx
	movl	$14, %edx
	movl	%eax, %edi
	call	set_gate
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	set_intr_gate, .-set_intr_gate
	.globl	set_sys_gate
	.type	set_sys_gate, @function
set_sys_gate:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rsi
	movl	-4(%rbp), %eax
	movl	$3, %ecx
	movl	$15, %edx
	movl	%eax, %edi
	call	set_gate
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE23:
	.size	set_sys_gate, .-set_sys_gate
	.globl	trap_init
	.type	trap_init, @function
trap_init:
.LFB24:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	divide_error@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	set_trap_gate
	movq	debug@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$1, %edi
	call	set_trap_gate
	movq	nmi@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$2, %edi
	call	set_trap_gate
	movq	int3@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$3, %edi
	call	set_trap_gate
	movq	overflow@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$4, %edi
	call	set_trap_gate
	movq	bounds@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$5, %edi
	call	set_trap_gate
	movq	invalid_op@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$6, %edi
	call	set_trap_gate
	movq	device_not_available@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$7, %edi
	call	set_trap_gate
	movq	double_fault@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$8, %edi
	call	set_trap_gate
	movq	coprocessor_segment_overrun@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$9, %edi
	call	set_trap_gate
	movq	invalid_TSS@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$10, %edi
	call	set_trap_gate
	movq	segment_not_present@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$11, %edi
	call	set_trap_gate
	movq	stack_segment@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$12, %edi
	call	set_trap_gate
	movq	general_protection@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$13, %edi
	call	set_trap_gate
	movq	page_fault@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$14, %edi
	call	set_trap_gate
	movq	reserved@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$15, %edi
	call	set_trap_gate
	movq	coprocessor_error@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$16, %edi
	call	set_trap_gate
	movl	$17, -4(%rbp)
	jmp	.L35
.L36:
	movl	-4(%rbp), %eax
	movq	reserved@GOTPCREL(%rip), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	set_trap_gate
	addl	$1, -4(%rbp)
.L35:
	cmpl	$47, -4(%rbp)
	jle	.L36
	movq	irq13@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$45, %edi
	call	set_trap_gate
	movq	parallel_interrupt@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$39, %edi
	call	set_trap_gate
	movl	$33, %eax
	movl	%eax, %edx
#APP
# 162 "traps.c" 1
	inb %dx,%al
	jmp 1f
1:	jmp 1f
1:
# 0 "" 2
#NO_APP
	movb	%al, -10(%rbp)
	movzbl	-10(%rbp), %eax
	movzbl	%al, %eax
	andl	$251, %eax
	movl	$33, %edx
#APP
# 162 "traps.c" 1
	outb %al,%dx
	jmp 1f
1:	jmp 1f
1:
# 0 "" 2
#NO_APP
	movl	$161, %eax
	movl	%eax, %edx
#APP
# 163 "traps.c" 1
	inb %dx,%al
	jmp 1f
1:	jmp 1f
1:
# 0 "" 2
#NO_APP
	movb	%al, -9(%rbp)
	movzbl	-9(%rbp), %eax
	movzbl	%al, %eax
	andl	$223, %eax
	movl	$161, %edx
#APP
# 163 "traps.c" 1
	outb %al,%dx
# 0 "" 2
#NO_APP
	movl	$54, %eax
	movl	$67, %edx
#APP
# 164 "traps.c" 1
	outb %al,%dx
	jmp 1f
1:	jmp 1f
1:
# 0 "" 2
#NO_APP
	movl	$155, %eax
	movl	$64, %edx
#APP
# 165 "traps.c" 1
	outb %al,%dx
	jmp 1f
1:	jmp 1f
1:
# 0 "" 2
#NO_APP
	movl	$46, %eax
	movl	$64, %edx
#APP
# 166 "traps.c" 1
	outb %al,%dx
# 0 "" 2
#NO_APP
	movq	timer_interrupt@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$32, %edi
	call	set_intr_gate
	movl	$33, %eax
	movl	%eax, %edx
#APP
# 168 "traps.c" 1
	inb %dx,%al
	jmp 1f
1:	jmp 1f
1:
# 0 "" 2
#NO_APP
	movb	%al, -8(%rbp)
	movzbl	-8(%rbp), %eax
	movzbl	%al, %eax
	andl	$-2, %eax
	movl	$33, %edx
#APP
# 168 "traps.c" 1
	outb %al,%dx
# 0 "" 2
#NO_APP
	movq	keyboard_interrupt@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$33, %edi
	call	set_intr_gate
	movl	$33, %eax
	movl	%eax, %edx
#APP
# 172 "traps.c" 1
	inb %dx,%al
	jmp 1f
1:	jmp 1f
1:
# 0 "" 2
#NO_APP
	movb	%al, -7(%rbp)
	movzbl	-7(%rbp), %eax
	movzbl	%al, %eax
	andl	$253, %eax
	movl	$33, %edx
#APP
# 172 "traps.c" 1
	outb %al,%dx
	jmp 1f
1:	jmp 1f
1:
# 0 "" 2
#NO_APP
	movl	$97, %eax
	movl	%eax, %edx
#APP
# 173 "traps.c" 1
	inb %dx,%al
	jmp 1f
1:	jmp 1f
1:
# 0 "" 2
#NO_APP
	movb	%al, -6(%rbp)
	movzbl	-6(%rbp), %eax
	movb	%al, -5(%rbp)
	movzbl	-5(%rbp), %eax
	orl	$-128, %eax
	movzbl	%al, %eax
	movl	$97, %edx
#APP
# 174 "traps.c" 1
	outb %al,%dx
	jmp 1f
1:	jmp 1f
1:
# 0 "" 2
#NO_APP
	movzbl	-5(%rbp), %eax
	movl	$97, %edx
#APP
# 175 "traps.c" 1
	outb %al,%dx
# 0 "" 2
#NO_APP
	movq	system_call@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$128, %edi
	call	set_sys_gate
#APP
# 179 "traps.c" 1
	sti
# 0 "" 2
#NO_APP
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE24:
	.size	trap_init, .-trap_init
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
