BITS 16
SYSSIZE equ 0x3000

BOOTSEG equ 0x07c0
INITSEG equ 0x9000
SETUPSEG equ 0x9020
SYSSEG equ 0x1000
ENDSEG equ SYSSEG + SYSSIZE

SETUPLEN equ 4

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
    mov ax,0x0200+SETUPLEN
    int 0x13
    jnc ok_load_setup
    mov ax,0x0000
    int 0x13 
    jmp  con
ok_load_setup:
; load setup to 0x90200
    mov dl,0x0
    mov ax,0x0800
    int 0x13
    mov ch,0x0
stp: jc stp
    cmp cx, 0
    jnz ok
    mov cx,18
ok:
    mov [sectors],cx
    mov ax,SYSSEG
    mov es,ax
    call read_it
    call kill_motor
    call disp
    jmp SETUPSEG:0

sread: dw 1 + SETUPLEN
head: dw 0
track: dw 0

read_it:
    mov ax,es             ; es->dest
    test ax,0x0fff
die: jne die
    xor bx,bx
rp_read:
   mov ax,es
   cmp ax,ENDSEG
   jb ok1_read
   ret
ok1_read:
    mov ax,[sectors]
    sub ax,[sread]
    mov cx,ax
    shl cx,9
    add cx,bx
    jnc ok2_read      ; < one seg
    je ok2_read       ; or = one seg
    xor ax,ax
    sub ax,bx
    shr ax,9
ok2_read:
    call read_track
    mov cx,ax
    add ax,[sread]
    cmp ax,[sectors]
    jne ok3_read
    mov ax,1
    sub ax,[head]
    jne ok4_read
    inc byte [track]
ok4_read:
    mov [head],ax
    xor ax,ax
ok3_read:
    mov [sread],ax
    shl cx,9
    add bx,cx
    jnc rp_read
    mov ax,es
    add ax,0x1000
    mov es,ax
    xor bx,bx
    jmp rp_read

read_track:
    push ax
    push bx
    push cx
    push dx
    mov dx,[track]
    mov cx,[sread]
    inc cx
    mov ch,dl
    mov dx,[head]
    mov dh,dl
    mov dl,0
    and dx,0x0100
    mov ah,2
    int 0x13
    jc bad_rt
    pop dx
    pop cx
    pop bx
    pop ax
    ret
bad_rt: 
    mov ax,0
    mov dx,0
    int 0x13
    pop dx
    pop cx
    pop bx
    pop ax
    jmp read_track

kill_motor:
    push dx
    mov dx,0x3f2
    mov al,0
    ;outb 
    pop dx
    ret
sectors: dw 0

disp:
    pusha
    push es
    mov ax,INITSEG
    mov es,ax
    mov ah,0x3
    xor bx,bx
    int 0x10
    mov cx,24
    mov bx,0x7
    mov bp,msg
    mov ax, 0x1301
    int 0x10
    pop es
    popa
    ret

section .data
msg:
    db 0xd, 0xa
    db "Loading system ..."
    db 0xd,0xa, 0xd,0xa
err:
    db "Error read disk!"
