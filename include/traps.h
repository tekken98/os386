#ifndef TRAPS_H
#define TRAPS_H
#include "types.h"
void set_trap_gate(uint num, void* fun);
void set_intr_gate(uint num,void *fun);
void set_sys_gate(uint n,void *fun);
#endif

