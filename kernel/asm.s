extern do_divide_error,do_debug,do_nmi,do_int3,do_overflow,do_bounds,do_invalid_op
extern do_double_fault,do_coprocessor_segment_overrun
extern do_invalid_TSS,do_segment_not_present,do_stack_segment
extern do_general_protection,do_coprocessor_error,do_irq13,do_reserved
extern printk
global divide_error,debug,nmi,int3,overflow,bounds,invalid_op
global device_not_available,double_fault,coprocessor_segment_overrun
global invalid_TSS,segment_not_present,stack_segment,general_protection,page_fault,reserved,coprocessor_error,irq13,parallel_interrupt
;int0
divide_error:
    push do_divide_error
no_error_code:
    xchg eax,[esp]
    push ebx
    push ecx
    push edx
    push edi
    push esi
    push ebp
    push ds
    push es
    push fs
    push 0
    lea edx,[esp+44]
    push edx
    mov edx,0x10
    mov ds,dx
    call eax
    add esp,8
    pop fs
    pop es
    pop ds
    pop ebp
    pop esi
    pop edi
    pop edx
    pop ecx
    pop ebx
    pop eax
    iret
; int1--debug
debug: 
    push do_debug
    jmp no_error_code
;int2
nmi:
    push do_nmi
    jmp no_error_code
;int3 
int3:
    push do_int3
    jmp no_error_code
;int4
overflow:
    push do_overflow
    jmp no_error_code
;int5
bounds:
    push do_bounds
    jmp no_error_code
;int6
invalid_op:
    push do_invalid_op
    jmp no_error_code
;int9
coprocessor_segment_overrun:
    push do_coprocessor_segment_overrun
    jmp no_error_code
;int15
reserved:
    push do_reserved
    jmp no_error_code
;int45
irq13:
    iret
;int8
double_fault:
    push do_double_fault
error_code:
    xchg [esp+4],eax
    xchg [esp],ebx
    push ecx
    push edx
    push edi
    push esi
    push ebp
    push ds
    push es
    push eax
    lea eax,[esp+44]
    push eax
    mov eax,0x10
    mov ds,ax
    mov es,ax
    mov fs,ax
    call [ebx]
    add esp,8
    pop fs
    pop es
    pop ds
    pop ebp
    pop esi
    pop edi
    pop ecx
    pop ebx
    pop eax
    iret
;int10
invalid_TSS:
    push do_invalid_TSS
    jmp error_code
;int11
segment_not_present:
    push do_segment_not_present
    jmp error_code
;int12
stack_segment:
    push do_stack_segment
    jmp error_code
;int13
general_protection:
    push do_general_protection
    jmp error_code
msg:    db 'eax=%x',0xa,0x0
device_not_available:
page_fault:
coprocessor_error:
timer_interrupt:
parallel_interrupt:
