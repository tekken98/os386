#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <m.h>
#include "vstring.h"
#define IO_BITMAP_SIZE 16

struct task_struct
{
    volatile long state;
    ulong esp;
    ulong ss;
    char name[64];
    ulong running;
    ulong times;
    ulong pid;
};
#define INIT_TASK \
    {  \
    0x78,79,0x80,"good",\
    1,0,0}
union task_union {
    struct task_struct task;
    char stack[4096];
};

struct tss_struct{
    ushort back_link,__blh;
    ulong esp0;
    ushort ss0,__ss0h;
    ulong espl;
    ushort ss1,__ss1h;
    ulong esp2;
    ushort ss2,__ss2h;
    ulong __cr3;
    ulong eip;
    ulong eax,ecx,edx,ebx;
    ulong esp,ebp,esi,edi;
    ushort es,__esh,cs__csh,ss,__ssh,ds,__dsh,fs__fsh,gs,__gsh,ldt,__ldth;
    ushort trace,bitmap;
    ulong io_bitmap[IO_BITMAP_SIZE+1];
    long __cahceline_filler[5];
};
#define INIT_TSS { \
    0,0,\
        sizeof(init_stack) + (long)&init_stack,\
        __KERNEL_DS,0,\
        0,0,0,0,0,0,\
        0,//cr3\
        0,0,\
        0,0,0,0,\
        0,0,0,0,\
        0,0,0,0,0,0,\
        0,0,0,0,0,0,\
        __LDT(0),0\
            0,INVALID_IO_BITMAP_OFFSET,\
        {~0,}\
}
static inline struct task_struct * get_current(void){
    struct task_struct * current;
    asm("andl %%esp,%0;":"=r"(current) : "0"(~4095UL));
    return current;
}
#define current get_current()

#define alloc_task_struct(p) \
    struct task_struct *p = (struct task_struct* )get_free_page();
#endif
