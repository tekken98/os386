#include "types.h"
#define PCI_IOPORT 1
#ifdef PCI_IOPORT
#define def_out(size,type) \
    extern void out##size(type value,u32 addr) { \
        asm volatile ("mov %1, %%edx; out %0,%%dx"::"a"(value),"r"(addr):"dx");}
        //asm volatile ("mov %1, %%edx; out %0,%%dx"::"a"(value),"r"(addr):"dx");}

#define def_in(size,type) \
    extern type in##size(u32 addr) { \
        type ret; \
        asm volatile ("mov" " %1,%%edx;in" #size " %%dx":"=a"(ret):"0"(addr)); return ret;}
        //asm volatile ("mov" " %1,%%edx;in" #size " %%dx":"=a"(ret):"0"(addr)); return ret;}
#else
#define def_out(size,type) \
    extern void out##size(type value,u32 addr) { \
        asm volatile ("mov" #size " %0,%1"::"r"(value),"m"(*(type*)addr));}
#define def_in(size,type) \
    extern type in##size(u32 addr) { \
        type ret; \
        asm volatile ("mov" #size " %1,%0":"=r"(ret):"m"(*(type*)addr)); return ret;}
#endif
def_in(b,u8);
def_in(w,u16);
def_in(l,u32);
def_out(b,u8);
def_out(w,u16);
def_out(l,u32);

u32 read_pci_config(u8 bus, u8 slot, u8 func, u8 offset)
{
	u32 v;
	outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | offset, 0xcf8);
	v = inl(0xcfc);
	return v;
}

u8 read_pci_config_byte(u8 bus, u8 slot, u8 func, u8 offset)
{
	u8 v;
	outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | offset, 0xcf8);
	v = inb(0xcfc + (offset&3));
	return v;
}

u16 read_pci_config_16(u8 bus, u8 slot, u8 func, u8 offset)
{
	u16 v;
	outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | offset, 0xcf8);
	v = inw(0xcfc + (offset&2));
	return v;
}

void write_pci_config(u8 bus, u8 slot, u8 func, u8 offset,
				    u32 val)
{
	outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | offset, 0xcf8);
	outl(val, 0xcfc);
}

void write_pci_config_byte(u8 bus, u8 slot, u8 func, u8 offset, u8 val)
{
	outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | offset, 0xcf8);
	outb(val, 0xcfc + (offset&3));
}

void write_pci_config_16(u8 bus, u8 slot, u8 func, u8 offset, u16 val)
{
	outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | offset, 0xcf8);
	outw(val, 0xcfc + (offset&2));
}

int early_pci_allowed(void)
{
//	return (pci_probe & (PCI_PROBE_CONF1|PCI_PROBE_NOEARLY)) == PCI_PROBE_CONF1;
    return 1;
}

