#include "types.h"
#include "io.h"
#include "vstring.h"
#include "sched.h"
#define HZ 100
#define LATCH (1193180/HZ)
long volatile jiffies =0;
extern void hd_init(void);
void hd_interrupt();
void timer_interrupt();
void keyboard_interrupt();
uchar tty_get_char();
void system_call();
void divide_error(void);
void debug(void);
void nmi(void);
void int3(void);
void overflow(void);
void bounds(void);
void invalid_op(void);
void device_not_available(void);
void double_fault(void);
void coprocessor_segment_overrun(void);
void invalid_TSS(void);
void segment_not_present(void);
void stack_segment(void);
void general_protection(void);
void page_fault(void);
void coprocessor_error(void);
void reserved(void);
void parallel_interrupt(void);
void irq13(void);
void do_double_fault(long esp,long error_code){
    printk("do_double_fault\n");
}
void do_general_protection(long esp,long error_code){
    printk("do_general_protection\n");
}
void do_divide_error(int esp, int error_code){
    printk("do_divide_error\n");
}
void do_int3(long esp,long error_code){
    printk("do_int3\n");
}
void do_nmi(long esp,long error_code){
    printk("do_nmi\n");
}
void do_debug(long esp,long error_code){
    printk("do_debug\n");
}
void do_overflow(long esp,long error_code){
    printk("do_overflow\n");
}
void do_bounds(long esp,long error_code){
    printk("do_bounds\n");
}
void do_invalid_op(long esp,long error_code){
    printk("do_invalid_op\n");
}
void do_device_not_available(long esp,long error_code){
    printk("do_device_not_available\n");
}
void do_coprocessor_segment_overrun(long esp,long error_code){
    printk("do_coprocessor_segment_overrun\n");
}
void do_invalid_TSS(long esp,long error_code){
    printk("do_invalid_TSS\n");
}
void do_segment_not_present(long esp,long error_code){
    printk("do_segment_not_present\n");
}
void do_stack_segment(long esp,long error_code){
    printk("do_stack_segment\n");
}
void do_coprocessor_error(long esp,long error_code){
    printk("do_coprocessor_error\n");
}
void do_reserved(long esp,long error_code){
    printk("do_reserved\n");
}
void do_timer(){
    schedule();
}
void do_sys_call(uint n){
    printk("system call %d \n",n);
}
#define IDTTABLE 0x200000 + 0x1000 * 8
void set_gate(uint num, void* fun,uint type,uint dpl){
    if (fun == 0x0){
        printk("int %d \n",num);
        return;
    }
    ushort i = (0x8000 + (dpl << 13) + (type << 8));
    asm("    shl $0x3, %%ecx\t\n"
            "mov $0x10,%%bx \t\n"
            "mov %%bx,%%ds \t\n"
            "mov %3,%%ebx \t\n"
            "mov $0x080000,%%edx \t\n"
            "mov %%ax,%%dx \t\n"
            "mov %0,%%ax \t\n"
            "add %%ecx,%%ebx \t\n"
            "mov %%edx,(%%ebx) \t\n"
            "add $0x4 , %%ebx \t\n"
            "mov %%eax,(%%ebx) \t\n"
            ::"o" (i), "c"(num),"a"(fun),"i"(IDTTABLE):"ebx","edx");
}

void set_trap_gate(uint num, void* fun){
    set_gate(num,fun,15,0);
}
void set_intr_gate(uint num,void *fun){
    set_gate(num,fun,14,0);
}
void set_sys_gate(uint n,void *fun){
    set_gate(n,fun,15,3);
}
void __stack_chk_fail(){
};
void trap_init(void){
    //for (int i = 0;i < 256;i++)
     //   set_trap_gate(i,&divide_error);
    set_trap_gate(0,&divide_error);
    set_trap_gate(1,&debug);
    set_trap_gate(2,&nmi);
    set_trap_gate(3,&int3);
    set_trap_gate(4,&overflow);
    set_trap_gate(5,&bounds);
    set_trap_gate(6,&invalid_op);
    set_trap_gate(7,&device_not_available);
    set_trap_gate(8,&double_fault);
    set_trap_gate(9,&coprocessor_segment_overrun);
    set_trap_gate(10,&invalid_TSS);
    set_trap_gate(11,&segment_not_present);
    set_trap_gate(12,&stack_segment);
    set_trap_gate(13, &general_protection);
    set_trap_gate(14,&page_fault);
    set_trap_gate(15,&reserved);
    set_trap_gate(16,&coprocessor_error);
    for(int i = 17;i<48;i++)
        set_trap_gate(i,&reserved);
    set_trap_gate(45,&irq13);
    set_trap_gate(39,&parallel_interrupt);
// time interrupt
    outb_p(inb_p(0x21)&0xfb,0x21);
    outb(inb_p(0xa1)&0xdf,0xa1);
    outb_p(0x36,0x43);
    outb_p(LATCH & 0xff,0x40);
    outb(LATCH >> 8 , 0x40);
    set_intr_gate(0x20,&timer_interrupt);
    outb(inb_p(0x21)&~0x01,0x21);
// keyboard interrupt 
    unsigned char a;
    set_intr_gate(0x21,&keyboard_interrupt);
    outb_p(inb_p(0x21)&0xfd,0x21);
    a = inb_p(0x61);
    outb_p(a|0x80,0x61);
    outb(a,0x61);
// system_call interrupt
    set_sys_gate(0x80,&system_call);

    hd_init();
    sti();
}
