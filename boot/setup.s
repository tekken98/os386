BITS 16
    INITSET equ 0x9000
    SYSSEG equ 0x1000
    SETUPSEG equ 0x9020

    cli
    cld
    mov ax,0
do_move:
    mov es,ax
    add ax,0x1000
    cmp ax,0x9000
    jz end_move
    mov ds,ax
    sub di,di
    sub si,si
    mov cx,0x8000
    rep movsw
    jmp do_move
end_move:
    mov ax,SETUPSEG
    mov ds,ax
    lidt [idt_48]
    lgdt [gdt_48]

    call empty_8042
    mov al,0xd1
    out 0x64,al
    call empty_8042
    mov al,0xdf
    out 0x60,al
    call empty_8042


    mov al,0x11
    out 0x20,al
    dw 0x00eb,0x00eb
    out 0xa0,al
    dw 0x00eb,0x00eb
    mov al,0x20
    out 0x21,al
    dw 0x00eb,0x00eb
    mov al,0x28
    out 0xa1,al
    dw 0x00eb,0x00eb
    mov al,0x04
    out 0x21,al
    dw 0x00eb,0x00eb
    mov al,0x02
    out 0xa1,al
    dw 0x00eb,0x00eb
    mov al,0x01
    out 0x21,al
    dw 0x00eb,0x00eb
    out 0xa1,al
    dw 0x00eb,0x00eb
    mov al,0xff
    out 0x21,al
    dw 0x00eb,0x00eb
    out 0xa1,al

    mov ax,0x1
    lmsw ax
    jmp 8:0

empty_8042:
    dw 0x00eb,0x00eb
    in al,0x64
    test al,0x2
    jnz empty_8042
    ret

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
    dw 512+gdt,0x9


