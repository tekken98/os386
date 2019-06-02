BITS 16
INITSEG equ 0x9000
BOOTSEG equ 0x07c0

section .text
global start
start:
    mov ax,BOOTSEG
    mov ds,ax
    mov ax,INITSEG
    mov ss,ax
    mov es,ax
    mov sp,0xffff
    xor si,si
    xor di,di
    mov cx,256
    rep movsw
    jmp INITSEG:con
con:
    mov ax,cs
    mov ds,ax
    mov dx,0x0000
    mov cx,0x0002
    mov bx,0x0200
    mov ax,0x0200+4
    int 0x13
    jnc ok_load_setup
    mov ax,0x0000
    int 0x13 
    jmp  con
ok_load_setup:
    call disp
    cli
    mov di,0
    mov si,0x200
    mov cx,0x200*2
    mov ax,0
    mov es,ax
    rep movsw
    mov ax,INITSEG
    mov dx,ax
    lidt [idt_48]
    lgdt [gdt_48]

    call empty_8042
    mov al,0xd1
    out 0x64,al
    call empty_8042
    mov al,0xdf
    out 0x60,al
    call empty_8042

    mov ax,0x1
    lmsw ax
    jmp 8:0

empty_8042:
    dw 0x00eb,0x00eb
    in al,0x64
    test al,0x2
    jnz empty_8042
    ret

disp:
    mov ah,0x3
    xor bx,bx
    int 0x10
    mov cx,24
    mov bx,0x7
    mov bp,msg
    mov ax, 0x1301
    int 0x10
    ret

section .data
msg:
    db 13,10
msgbegin:
    db "Loading system ..."
    db 13,10,13,10
gdt:
    dw 0,0,0,0

    dw 0xffff
    dw 0x0000
    dw 0x9a00
    dw 0x00c0

    dw 0xffff
    dw 0x0000
    dw 0x9200
    dw 0x00c0
idt_48:
    dw 0
    dw 0,0
gdt_48:
    dw 0x800
    dw gdt,0x9


