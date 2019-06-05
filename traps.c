void printk(const char*,...);
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
#pragma align 8
void set_trap_gate(int num, void* fun){
    asm("    shl $3, %%ecx\t\n"
            "mov $0x10,%%bx \t\n"
            "mov %%bx,%%ds \t\n"
            "mov $0x90000,%%ebx \t\n"
            "mov $0x080000,%%edx \t\n"
            "mov %%ax,%%dx \t\n"
            "mov $0x8e00,%%ax \t\n"
            "add %%ecx,%%ebx \t\n"
            "mov %%edx,(%%ebx) \t\n"
            "add $0x4 , %%ebx \t\n"
            "mov %%eax,(%%ebx) \t\n"
            ::"c"(num),"a"(fun):"ebx","edx");
}
void sti(){
    asm("sti");
}
void trap_init(void){
    //for (int i = 0;i < 256;i++)
    set_trap_gate(0,divide_error);
    set_trap_gate(1,debug);
    set_trap_gate(2,nmi);
    set_trap_gate(3,int3);
    set_trap_gate(4,overflow);
    set_trap_gate(5,bounds);
    set_trap_gate(6,invalid_op);
    set_trap_gate(7,device_not_available);
    set_trap_gate(8,double_fault);
    set_trap_gate(9,coprocessor_segment_overrun);
    set_trap_gate(10,invalid_TSS);
    set_trap_gate(11,segment_not_present);
    set_trap_gate(12,stack_segment);
    set_trap_gate(13, general_protection);
    set_trap_gate(14,page_fault);
    set_trap_gate(15,reserved);
    set_trap_gate(16,coprocessor_error);
    for(int i = 17;i<48;i++)
        set_trap_gate(i,reserved);
    set_trap_gate(45,irq13);
    /*asm("in $0x21,%%ax \t\n"
            "and $0xfb,%%al\t\n"
            "out %%al,0x21\t\n"
            "in $0xa1\t\n"
            "and $xdf,%%al\t\n"
            "out %%al,$0xa1 \t\n");
            */
    //outb_p(inb_p(0x21)&0xfb,0x21);
    //outb(inb_p(0xa1)&0xdf,0xa1);
    set_trap_gate(39,parallel_interrupt);
    sti();
    int a = 1 / 0;
}
