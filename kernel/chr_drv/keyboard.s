BITS 32
global keyboard_interrupt
extern printk
extern backspace
keyboard_interrupt:
    push edx
    push ebx
    push ecx
    push edx
    push ds
    push es
    mov eax,0x10
    mov ds,ax
    mov es,ax
    xor al,al
    in al,0x60
    cmp al,0xe0
    je set_e0
    cmp al,0xe1
    je set_e1
    test al,0x80
    jnz up
    call filter
    xor ecx,ecx
    mov cl,[keymap+eax]
    push ecx
    push key
    call printk
    ;call key_table + eax * 4
    add esp,8
up:
    mov byte [e0],0;
e0_e1:
    in al,0x61
    jmp j1
j1:  jmp j2
j2:  or al,0x80
    jmp j3
j3:  jmp j4
j4:  out 0x61,al
    jmp j5
j5:  jmp j6
j6:  and al,0x7f
    out 0x61,al
    mov al,0x20
    out 0x20,al
    push 0
    ;call do_tty_interrupt
    add esp,4
    pop es
    pop ds
    pop edx
    pop ecx
    pop ebx
    pop eax
    iret
set_e0:
    mov byte [e0],1
    jmp e0_e1
set_e1:
    mov byte [e0],2
    jmp e0_e1
filter:
    cmp  al,0xe
    jnz f_ret
    call backspace
    add esp,4
    jmp up
f_ret:
    ret


key:    
    db "%c",0x0
special:
    db " key special %x ",0xa,0x0
e0: db 0
keymap:
    db 00,27
    db '1234567890-='
    db 127,9
    db 'qwertyuiop[]'
    db 13,0
    db "asdfghjkl;'`"
    db 0,'\zxcvbnm,./',0
    db '*',0,32   ; 36-39
    times 16 db 0      ; 3a-49
    db '-',0,0,0,'+'
    db 0,0,0,0,0,0,0
    db '<'
    times 10 db 0
