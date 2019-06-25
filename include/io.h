#ifndef IO_H
#define IO_H
#include "pci.h"
#define iooutb(value,port)\
    asm("outb %%al,%%dx"::"a"(value),"d"(port));
#define inb(port)({\
        unsigned char _v;\
        asm volatile("inb %%dx,%%al" : "=a"(_v):"d"(port));\
        _v;})
#define outb_p(value,port)\
    asm("outb %%al,%%dx\n"\
            "\tjmp 1f\n"\
            "1:\tjmp 1f\n"\
            "1:"::"a"(value),"d"(port))
#define inb_p(port) ({\
        unsigned char _v;\
        asm volatile ("inb %%dx,%%al\n"\
                "\tjmp 1f\n"\
                "1:\tjmp 1f\n"\
                "1:" \
                :"=a"(_v) :"d"(port));\
        _v;})
#define sti() asm("sti");
#define cli() asm("cli");
#define nop() asm("nop");
#endif

