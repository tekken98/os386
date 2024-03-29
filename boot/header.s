BITS 32
mem_size     equ 0x20 << 20 ; 32M 8 pages
SYSTEM       equ 0x100000
PGDIR        equ 0x200000 ; 1M
PG0          equ 0x201000 + PGDIR
PGNUMS       equ 0x8
IDTTABLE     equ 0x208000  ; 64k
GDTTABLE     equ 0x208000 + 256 * 8; 64k
VIDEOADDR    equ 0xb8000
%macro  updateReg 0
    mov ax,0x10
    mov es,ax
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax
    mov esp,0x8ffff
%endmacro 
extern mmain
extern printk
global _start
section .text
_start:
    mov ax,cs
    mov ds,ax
    mov es,ax
    updateReg 
    mov edi,SYSTEM
    xor esi,esi
    mov eax, 0x90a00-0x4
    mov ecx,[eax]
    shr ecx,2
    rep movsd
    jmp 0x8: con
con:
    call setup_idt
    call setup_gdt
    updateReg
    xor eax,eax
    call setup_pages
    call disp
    call mmain
stop:
    hlt
    jmp stop

disp:
    mov edi,VIDEOADDR
    mov cx,4
    mov esi,msg
load:
    lodsb
    stosb
    mov al,15
    stosb
    dec cx
    jnz load
    ret

setup_idt:
    lea edx,[ignore_int]
    mov eax,0x80000
    mov ax,dx
    mov dx,0x8e00
    mov edi,IDTTABLE
    mov ecx,256
rp_sidt:
    mov [edi],eax
    mov [edi + 4],edx
    add edi,0x8
    dec ecx
    jne rp_sidt
    lidt [idt_descr]
    ret
setup_gdt:
    mov esi,gdt
    mov edi, IDTTABLE + 256*8
    mov cx,4 * 4
    rep movsd
    lgdt [gdt_descr]
    ret

setup_pages:
    mov ecx,1024*(PGNUMS + 1)
    xor eax,eax
    mov edi,PGDIR
    cld
    res stosd
    mov ebx,PGDIR
    mov eax,PG0
    add eax,0x7
    mov ecx,PGNUMS
setpg:
    mov [ebx],eax
    add eax,0x1000
    add ebx,0x4
    dec cx
    jnz setpg

    mov cx,1024 * 8
    mov edi,PG0
    mov eax,0x7

nextpg:
    stosd
    add eax,0x1000
    dec cx
    jnz  nextpg
    mov  eax,PGDIR
    mov cr3,eax
    mov eax,cr0
    or eax,0x80000000
    mov cr0,eax
    ret


ignore_int:
    push ebx
    push eax
    mov eax,[esp+12]
    mov ebx,[esp+8]
    pusha
    push esp
    push ebx
    push eax
    push initmsg
    call printk
    ;mov al,0x20
    ;out 0x20,al
    pop eax
    pop eax
    pop eax
    pop ebx
    popa
    add esp,8
    iret
msg db 'head!',0xa,0x0
initmsg db "cs=%x,eip=%x,esp=%x",0xa,0x0
align 0x2
idt_descr:
    dw 256*8-1
    dd IDTTABLE
gdt_descr:
    dw 256*8 - 1
    dd GDTTABLE
gdt:
    dq 0x0000000000000000
    dq 0x00cf9a0000001fff ; 32M 0x8 _cs  0x00c09a0000001fff  user define bits
    dq 0x00cf920000001fff ; 32M 0x10 _ds
    dq 0x00cffa0000001fff ; 32M 0x18 user_cs
    dq 0x00cff20000001fff ; 32M 0x20 user_ds
    dq 0x0000000000000000

