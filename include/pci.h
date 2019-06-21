#ifndef PCI_H
#define PCI_H
#include "types.h"
#include "pci_regs.h"
u32 inl(u32 addr);
u16 inw(u16 addr);
u8 inb(u8 addr);
void outb(u8 value,u32 addr);
void outw(u16 value,u32 addr);
void outl(u32 value,u32 addr);
u32 read_pci_config(u8 bus, u8 slot, u8 func, u8 offset);
u8 read_pci_config_byte(u8 bus, u8 slot, u8 func, u8 offset);
u16 read_pci_config_16(u8 bus, u8 slot, u8 func, u8 offset);
void write_pci_config(u8 bus, u8 slot, u8 func, u8 offset,u32 val);
void write_pci_config_byte(u8 bus, u8 slot, u8 func, u8 offset, u8 val);
void write_pci_config_16(u8 bus, u8 slot, u8 func, u8 offset, u16 val);
#define pci_addr(bus,dev,fn,offset) (0x80000000 | bus << 16 | dev << 11 | fn << 8|offset)
#endif
