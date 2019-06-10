BITS 32
section .text
global timer_interrupt,system_call
extern do_timer
extern jiffies
extern do_sys_call
timer_interrupt:
    push ds
    push es
    push fs
    push edx
    push ecx
    push ebx
    push eax
    mov eax,0x10
    mov ds,ax
    mov es,ax
    mov eax,0x17
    ;mov fs,ax
    inc word [jiffies]
    mov al,0x20
    out 0x20,al
    mov eax,[cs:esp]
    and eax,0x3
    push eax
    call do_timer
    add esp,0x4
    jmp ret_from_sys_call
ret_from_sys_call:
    pop eax
    pop ebx
    pop ecx
    pop edx
    pop fs
    pop es
    pop ds
    iret
align 2
system_call:
    push ds
    push es
    push fs
    push edx
    push ecx
    push ebx
    mov edx,0x10
    mov ds,dx
    mov es,dx
    mov dx,0x20
    mov fs,dx
    push eax
    call do_sys_call
    add esp,4
    pop ebx
    pop ecx
    pop edx
    pop fs
    pop es
    pop ds
    iret
