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
}
void do_general_protection(long esp,long error_code){
}

void do_divide_error(int esp, int error_code){
    printk("do_divide_error\n");
}
void do_int3(long esp,long error_code){
}
void do_nmi(long esp,long error_code){
}
void do_debug(long esp,long error_code){
}
void do_overflow(long esp,long error_code){
}
void do_bounds(long esp,long error_code){
}
void do_invalid_op(long esp,long error_code){
}
void do_device_not_available(long esp,long error_code){
}
void do_coprocessor_segment_overrun(long esp,long error_code){
}
void do_invalid_TSS(long esp,long error_code){
}
void do_segment_not_present(long esp,long error_code){
}
void do_stack_segment(long esp,long error_code){
}
void do_coprocessor_error(long esp,long error_code){
}
void do_reserved(long esp,long error_code){
}
#pragma align 8
void set_trap_gate(int num, void* fun){
    printk("fun addr %x \n",fun);
    asm("    shl $3, %%ecx\t\n"
            "mov $0x10,%%bx \t\n"
            "mov %%bx,%%ds \t\n"
            "mov $0x10000,%%ebx \t\n"
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
    sti();
    int a  = 1 / 0;
}
