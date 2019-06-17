#ifndef M_H
#define M_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif
struct mem_page {
    int size;
    ushort * free;
    struct mem_page * next;
    uint count;
};

ulong get_free_page(void);
uint new_mem_page(uint);
uint kmalloc(uint size);
void kfree(void *);
//void print_mem_page(struct mem_page*);
#ifdef __cplusplus
}
#endif
#endif

